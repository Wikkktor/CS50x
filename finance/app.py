import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    transactions = db.execute("SELECT symbol, name, SUM(shares) AS shares, price FROM history WHERE client_id = ? GROUP BY symbol", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id=?",session["user_id"])

    final_total = cash[0]['cash']
    for stock in transactions:
        price = lookup(stock['symbol'])["price"]
        total = stock["shares"] * price
        stock.update({"price": usd(price), 'total':usd(total)})
        final_total += total
    return render_template("index.html", cash=usd(cash[0]["cash"]), transactions=transactions, final_total=usd(final_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        response = lookup(symbol)
        if not symbol or not shares or not response:
            return apology("Invalid symbol or shares")
        try:
            shares = int(shares)
            if shares < 0:
                return apology("bad shares")


            price_for_share = response['price']
            total_price = price_for_share * int(shares)
            balance = db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"] )
            balance = balance[0]['cash']
            if balance > total_price:
                balance -= total_price
                db.execute("UPDATE users SET cash = ? WHERE id = ?",balance, session["user_id"] )
                db.execute("INSERT INTO history (client_id, action, symbol, shares, datetime, name, price)VALUES (?,?,?,?,?,?,?)", session["user_id"], 'buy', symbol, shares, str(datetime.now()), response["name"],price_for_share)
                flash("You bought a share!")
                return redirect("/")
            return apology("You don't have money")
        except (KeyError, TypeError, ValueError):
            return apology("Invalid shares")
    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    history = db.execute("SELECT * FROM history WHERE client_id = ?", user_id)
    return render_template("history.html", history = history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Invalid symbol")
        info = lookup(symbol)
        if not info:
            return apology("Invalid symbol")

        return render_template("quoted.html", name=info['name'], symbol=info['symbol'], price=usd(info['price']))

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        username = request.form.get("username")
        if not username:
            return apology("invalid username and/or password", 400)

        password  = request.form.get("password")
        if not password:
            return apology("invalid username and/or password", 400)

        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("invalid username and/or password", 400)

        if password != confirmation:
            return apology("passwords doesnt match", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) != 0:
            return apology("invalid username", 400)

        db.execute("INSERT INTO users (username, hash) VALUES (?,?)", username, generate_password_hash(password,method='pbkdf2:sha256', salt_length=8 ))
        row = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        session["user_id"] = row[0]["id"]
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol or not shares:
            return apology("Invalid symbol or shares")
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("invalid shares")
            available_shares = db.execute("SELECT SUM(shares) FROM history WHERE client_id = ? and symbol = ?", user_id, symbol)
            print(available_shares)
            if shares > available_shares[0]['SUM(shares)']:
                return apology("invalid_shares")
            response = lookup(symbol)
            price = response["price"]
            new_money = shares * int(price)
            before_cash = db.execute("SELECT cash from users WHERE id=?", user_id)
            before_cash = before_cash[0]["cash"]
            db.execute("UPDATE users SET cash = ? WHERE id = ?", before_cash + new_money, user_id)
            db.execute("INSERT INTO history (client_id, action, symbol, shares, datetime, name, price)VALUES (?,?,?,?,?,?,?)", session["user_id"], 'SELL', symbol, (-1 * shares), str(datetime.now), response["name"],price)
            return redirect("/")
        except (KeyError, TypeError, ValueError):
            return apology("Invalid shares")
    else:
        symbols = db.execute("SELECT symbol FROM history WHERE client_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)
        return render_template("sell.html", symbols=symbols)

@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash_add():
    """ Add cash to your account """
    user_id = session["user_id"]
    if request.method == "POST":
        new_cash = request.form.get("amount")
        if not new_cash:
            return apology("Wrong amount")
        try:
            cash = int(new_cash)
            if cash < 0:
                return apology("Wrong amount")
            actual_cash = db.execute("SELECT cash FROM users WHERE id =?", user_id)
            new_cash = actual_cash[0]["cash"] + cash
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)
            return redirect("/")
        except (KeyError, TypeError, ValueError):
            return apology("Wrong amount")
    else:
        return render_template("cash.html")