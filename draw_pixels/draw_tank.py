data_out = open("./tank_icon_enemy.dat", "w")

def change_xy(x1, y1):
    x2 = x1 * 2
    y2 = y1 * 2
    output = []
    output.append((x2+3, y2+3))
    output.append((x2+4, y2+3))
    output.append((x2+3, y2+4))
    output.append((x2+4, y2+4))
    return output

def draw_wheel(x, y):
    draw_pixels = change_xy(x,y)
    #print(draw_pixels)
    for i in draw_pixels:
        addr = hex(i[0]*32 + i[1]).replace("0x", "")
        #data_bin = "0000000101100001" 
        data_bin = "0000000000010000" 
        data_out.write(addr + "="  + data_bin + "\n")

def draw_body1(x, y):
    draw_pixels = change_xy(x,y)
    for i in draw_pixels:
        addr = hex(i[0]*32 + i[1]).replace("0x", "")
        #data_bin = "0000000111111100"
        data_bin = "0000000111111111" 
        data_out.write(addr + "="  + data_bin + "\n")

def draw_body2(x, y):
    draw_pixels = change_xy(x,y)
    for i in draw_pixels:
        addr = hex(i[0]*32 + i[1]).replace("0x", "")
        #data_bin = "0000000111101010" 
        data_bin = "0000000000011001" 
        data_out.write(addr + "="  + data_bin + "\n")
    
for x in range(0, 13):
    for y in range(0, 13):
        if x == 1 or x == 3 or x == 5 or x == 7 or x == 9:
            if y == 0 or y == 1 or y == 11 or y == 12:
                draw_wheel(x, y)
        if y == 10:
            if x >= 0 and x <= 10:
                draw_wheel(x, y)
        if x == 8:
            if y == 4 or y == 5 or y == 7 or y == 8:
                draw_wheel(x, y)
        if x == 0 or x == 2 or x == 4 or x == 6 or x == 8 or x == 10:
            if y == 1 or y == 11 or y == 12:
                draw_body2(x, y)
        if y == 1:
            if x >= 0 and x <= 10:
                draw_body1(x, y)
        if x == 0 or x == 2 or x == 4 or x == 6 or x == 8 or x == 10:
            if y == 0:
                draw_body2(x, y)

        #di
        if x == 1:
            if y >= 4 and y <= 8:
                draw_body1(x, y)

        #pao guan
        if y == 6:
            if x >= 8 and x <= 12:
                draw_body1(x, y)

        if x >= 2 and x <= 7:
            if y >= 3 and y <= 5:
                draw_body1(x, y)
        if x >= 2 and x <= 7:
            if y >= 6 and y <= 9:
                if (x == 6 and y == 6) or (x == 6 and y == 7) or (x == 5 and y == 7) or (x == 4 and y == 7):
                    draw_wheel(x, y)
                else:
                    draw_body2(x, y)
        
        
