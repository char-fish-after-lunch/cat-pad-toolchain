data_out = open("./text_icon.dat", "w")

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
        if x >= 3 and x <= 12 and y == 7:
            draw_black()
        elif x == 2 and y >= 4 and y <= 10:
            draw_black()
        else:
            draw_white()