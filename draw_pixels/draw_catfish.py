data_out = open("./catfish_icon.data", "w")

def draw_black():
    data_bin = "0000000000000000" 
    data_out.write(data_bin + "\n")

def draw_pink():
    data_bin = "0000000111110110" 
    data_out.write(data_bin + "\n")

def draw_white():
    data_bin = "0000000111111111" 
    data_out.write(data_bin + "\n")

for i in range(0, 16):
    for j in range(0, 16):
        if i < 3:
            draw_pink()
        elif i == 3:
            if j == 5 or j == 7 or j == 9:
                draw_black()
            else:
                draw_pink()
        elif i > 3 and j < 2:
            draw_pink()
        elif i == 4:
            if j == 2:
                draw_black()
            else:
                draw_pink()
        elif i == 5:
            if j == 2 or j == 3 or j == 15:
                draw_black()
            else:
                draw_pink()
        elif i == 6:
            if j == 2 or j == 4 or j == 14:
                draw_black()
            elif j == 3 or j == 15:
                draw_white()
            else:
                draw_pink()
        elif j == 2 and i > 6:
            draw_black()
        elif i == 7 and j > 4 and j < 14:
            draw_black()
        elif (i == 9 and j == 5) or (i == 9 and j == 6) or (i == 9 and j == 12) or (i == 9 and j == 13):
            draw_black()
        elif (i == 10 and j == 7) or (i == 10 and j == 11):
            draw_black()
        elif (i == 11 and j == 5) or (i == 11 and j == 6) or (i == 11 and j == 12) or (i == 11 and j == 13):
            draw_black()
        elif (i == 12 and j == 5) or (i == 12 and j == 6) or (i == 12 and j == 12) or (i == 12 and j == 13):
            draw_black()
        elif (i == 13 and j == 7) or (i == 13 and j == 9) or (i == 13 and j == 11):
            draw_black()
        elif (i == 14 and j == 7) or (i == 14 and j == 8) or (i == 14 and j == 9) or (i == 14 and j == 10) or (i == 14 and j == 11):
            draw_black()
        else:
            draw_white()
