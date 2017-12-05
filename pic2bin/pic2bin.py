import cv2

pic = cv2.imread("./pic.jpg")

data_out = open("./ram2.data", "w")

for i in range(512):
    for j in range(512):
        addr = hex(i*512 + j).replace("0x", "")
        if (i < 500 and j < 500):        
            data_int = int(pic[i][j][2] / 32) * 64 + int(pic[i][j][1] / 32) * 8 + int(pic[i][j][0] / 32)
        else:
            data_int = 7 * 64 + 7 * 8 + 7
        # print data_int
        data_hex = hex(data_int).replace("0x", "")
        data_out.write(addr + "=" + data_hex + "\n")

data_out.close()
