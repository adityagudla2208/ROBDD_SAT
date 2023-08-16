with open("input.txt", "r") as f:
    data = f.read()

result = ""

i = 0

while i < len(data):
    if data[i:i+2].isdigit():
        num = int(data[i:i+2]) + 5
        result += str(num)
        i += 2
    elif data[i].isdigit():
        if (data[i-1] == 'p' or data[i-1] == 'q' or data[i-1] == 'r' or data[i-1] == 's' or data[i-1] == 'x'):
            num = int(data[i]) + 1
        else:
            num = int(data[i]) + 5
        result += str(num)
        i += 1
    else:
        result += data[i]
        i += 1

with open("output.txt", "w") as f:
    f.write(result)
