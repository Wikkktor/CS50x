# TODO


def pyramide():
    while True:
        try:
            height = int(input("Height: "))
            if type(height) == int and  9 > height > 0:
                break
        except ValueError:
            pyramide()

    for i in range(height):
        print(" " * (height - i - 1), end='')
        print('#' * (i + 1), end='')
        print("  ", end='')
        print('#' * (i + 1))


pyramide()