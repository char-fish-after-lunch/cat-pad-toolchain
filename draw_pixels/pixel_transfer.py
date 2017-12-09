f = open("text_icon.dat", "r")
data_out = open("./text_icon_16.dat", "w")

# for l in f:
#     array = l.split('=')
#     n = int(array[1], base=2)
#     output = str(hex(n).replace("0x", ""))
#     data_out.write(array[0] + "="  + output + "\n")
# f.close()

for l in f:
    n = int(l, base=2)
    output = str(hex(n).replace("0x", ""))
    data_out.write(output + "\n")
f.close()