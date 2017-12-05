f = open("./origin.txt","r")

out_f = open("./out.txt", "w")

for l in f:
    if (not l.startswith("0")):
        continue
    # 0x00,0x7F,0x06,0x08,0x30,0x7F,0x00,0x00, /*"N"=2Eh*/
    t = l.split(",")
    s = t[8].replace("/*", "").replace("*/", "").replace('"', "")
    # print t
    p = s.split("=")
    ch = ord(p[0][1])
    
    chb = bin(ch).replace("0b", "")
    chb = "0" * (7-len(chb)) + chb
    out_f.write('when "' + chb + '" => --' + chr(ch) + "\n")
    
    ss = []
    for i in range(7, -1, -1):
        v = int(t[i], base=0)
        # print v
        b = bin(v).replace("0b", "")
        b = "0" * (8-len(b)) + b
        ss.append(b)

    for i in range(7, -1, -1):
        b = ("".join([ss[7-j][i] for j in range(8)]))
        out_f.write('    tmp_graphic(' + str(i*8+7) + ' downto ' + str(i*8) + ')   <= "' + b + '";\n')

    
