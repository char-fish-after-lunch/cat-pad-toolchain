data_out = open("./tank_icon.dat", "w")

def draw_black():
    data_bin = "0000000000000000" 
    data_out.write(data_bin + "\n")

def draw_pink():
    data_bin = "0000000111110110" 
    data_out.write(data_bin + "\n")

def draw_white():
    data_bin = "0000000111111111" 
    data_out.write(data_bin + "\n")
    
for x in range(0, 16):
    for y in range(0, 16):
        if x >= 1 and x <= 11:
            if (y >= 1 and y <= 3) or (y >= 11 and y <= 13):
                draw_black()
            elif x >= 2 and x <= 9 and y >= 4 and y <= 10:
                draw_black()
            elif y == 7 and x >= 9:
                draw_black()
            else:
                draw_white()
        else:
            draw_white()