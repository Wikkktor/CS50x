-- Keep a log of any SQL queries you execute as you solve the mystery.

-- checking list of crimes that happed that day at order.
SELECT *
  FROM crime_scene_reports
  WHERE year = 2021
  and day = 28
  and month =7
  ORDER BY 2, 3, 4;

-- 28 / 7 / 2021 10:15am Thief has stolen CS50 duck
-- Theft of the duck took place at 10:15am , 3 witnesses were present and they mentions bakery


-- Checking interviews with bakery in transcript

SELECT *
  FROM interviews
  WHERE year = 2021
  and day = 28
  and month = 7
  and transcript
  LIKE "%bakery%"
  ORDER BY 3,4,5;

-- Witnesses: Ruth, Eugene, Raymond
-- Ruth: bakery security footage, his car must have left
-- Eugene earlier that morning saw him at ATM withdrawing some money
-- Raymond thief is planing to take the earlist filght out of town tommorow , and thief asked to buy flight ticket

-- RUTH INFO
-- Due to Ruth there must be a plate of thief
SELECT hour,  minute, license_plate
  FROM bakery_security_logs
 WHERE year = 2021
   and day =28
   and month = 7
   and activity = "exit"
   and hour = 10
   and minute < 30
ORDER BY hour
   asc;

-- Names of people that left car that time  8 people
SELECT name
  FROM people
  JOIN bakery_security_logs
  ON people.license_plate = bakery_security_logs.license_plate
  WHERE year = 2021
  and day =28
  and month = 7
  and activity = "exit"
  and hour = 10
  and minute < 30
  ORDER BY hour
  asc;

-- | Vanessa |
-- | Bruce   |
-- | Barry   |
-- | Luca    |
-- | Sofia   |
-- | Iman    |
-- | Diana   |
-- | Kelsey

-- Checking passport number of people that left bakery parking when thief did
SELECT passport_number
  FROM people
  JOIN bakery_security_logs
    ON people.license_plate = bakery_security_logs.license_plate
 WHERE bakery_security_logs.year = 2021
   AND bakery_security_logs.day = 28
   AND bakery_security_logs.month = 7
   AND bakery_security_logs.activity = "exit"
   AND bakery_security_logs.hour = 10
   AND bakery_security_logs.minute < 30
   AND activity = "exit"
   AND hour = 10
   AND minute < 30
   ORDER BY hour
   asc;


-- Eugene info
-- Checking list of people that withdraw money 10 min after the robery
SELECT name
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
  JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
 WHERE atm_transactions.year = 2021
   AND atm_transactions.month = 7
   AND atm_transactions.day = 28
   AND atm_transactions.atm_location = 'Leggett Street'
   AND atm_transactions.transaction_type = 'withdraw';


-- | Bruce   |
-- | Diana   |
-- | Brooke  |
-- | Kenny   |
-- | Iman    |
-- | Luca    |
-- | Taylor  |
-- | Benista





--RAYMOND INFO



-- City that was  the earlies destination, day after thief stole duck from fiftyville ( New York City at 8 : 20 )
SELECT distinct(city), flights.hour, flights.minute
  FROM airports
  JOIN flights
  ON airports.id = flights.destination_airport_id
  WHERE flights.year = 2021
  and flights.day = 29
  and month = 7
  and flights.origin_airport_id = (
    SELECT id
    FROM airports
    WHERE city = "Fiftyville")
    ORDER BY hour
    asc
    LIMIT 1;

-- DESTINATION NEW YORK CITY !!!


-- Names of people that went on that flight ^
SELECT name
  FROM people
  JOIN passengers
  ON passengers.passport_number = people.passport_number
  WHERE passengers.flight_id = (
    SELECT id FROM flights
    WHERE year = 2021
    AND month = 7
    AND day = 29
    AND origin_airport_id = (
        SELECT id
        FROM airports
        WHERE city = "Fiftyville")
        ORDER BY hour,minute
        LIMIT 1
        );

-- | Doris  |
-- | Sofia  |
-- | Bruce  |
-- | Edward |
-- | Kelsey |
-- | Taylor |
-- | Kenny  |
-- | Luca

-- Checking all phone callers based on Raymond interview
SELECT name
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.caller
 WHERE phone_calls.year = 2021
   AND phone_calls.month = 7
   AND phone_calls.day = 28
   AND phone_calls.duration < 60
 ORDER BY phone_calls.duration;

-- | Kelsey  |
-- | Carina  |
-- | Taylor  |
-- | Bruce   |
-- | Diana   |
-- | Kelsey  |
-- | Sofia   |
-- | Benista |
-- | Kenny

-- Checking all phone call recivers

SELECT name
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.receiver
 WHERE phone_calls.year = 2021
   AND phone_calls.month = 7
   AND phone_calls.day = 28
   AND phone_calls.duration < 60
   ORDER BY phone_calls.duration;



--ACCOMPLICE-- !!!!!!!!!!!!!!
-- | Larry      |
-- | Jacqueline |
-- | James      |
-- | Robin      |
-- | Philip     |
-- | Melissa    |
-- | Jack       |
-- | Anna       |
-- | Doris


-- LOOKING FOR ACCOMPLICE , checking who Bruce called
SELECT name
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.receiver
 WHERE phone_calls.year = 2021
   AND phone_calls.month = 7
   AND phone_calls.day = 28
   AND phone_calls.duration < 60
      AND phone_calls.caller = (
        SELECT phone_number
        FROM people
        WHERE name = "Bruce"
        )
   ORDER BY phone_calls.duration;
-- RESULT ROBIN




-- BRUCE IS ON ALL LISTS HE IS A THIEF ROBIN IS ACCOMPLICE
