data_out = open("./keyboard.dat", "w")

def draw_white():
    data_bin = "0000000111111111" 
    data_out.write(data_bin + "\n")

def draw_black():
    data_bin = "0000000000000000" 
    data_out.write(data_bin + "\n")

for i in range(0, 16):
    for j in range(0, 16):
        if i >= 4 and i <= 10 and j >= 0 and j <= 14:
            if i == 5:
                if j == 2 or j == 4 or j == 7 or j == 9 or j == 11 or j == 13:
                    draw_white()
                else:
                    draw_black()
            elif i == 7:
                if j == 1 or j == 3 or j == 5 or j == 7 or j == 9 or j == 11 or j == 13:
                    draw_white()
                else:
                    draw_black()
            elif i == 9:
                if j == 1 or j == 2 or (j >= 4 and j <= 10) or j == 12 or j == 13:
                    draw_white()
                else:
                    draw_black()
            else:
                draw_black()
        else:
            draw_white()