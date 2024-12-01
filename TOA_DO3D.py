import serial
import matplotlib.pyplot as plt
import numpy as np

# Kết nối tới cổng COM
ser = serial.Serial('COM15', 57600)  # Thay đổi 'COM3' theo cổng mà Arduino đang kết nối

# Danh sách để lưu trữ tọa độ
x_values = []
y_values = []
z_values = []

# Thiết lập đồ thị
plt.ion()  # Chế độ tương tác
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Giới hạn giá trị đầu vào
x_min, x_max = -32768, 32767
y_min, y_max = -32768, 32767
z_min, z_max = -32768, 32767

while True:
    if ser.in_waiting > 0:  # Kiểm tra xem có dữ liệu không
        line = ser.readline().decode('utf-8').strip()  # Đọc dữ liệu
        if line:  # Nếu có dữ liệu
            try:
                # Tách dữ liệu và chuyển đổi thành số
                xMag, yMag, zMag = map(int, line.split(","))

                # Chuyển đổi giá trị sử dụng hàm map
                mappedX = np.clip(np.interp(xMag, [x_min, x_max], [0, 200]), 0, 200)
                mappedY = np.clip(np.interp(yMag, [y_min, y_max], [0, 200]), 0, 200)
                mappedZ = np.clip(np.interp(zMag, [z_min, z_max], [0, 200]), 0, 200)

                # Lưu trữ giá trị vào danh sách
                x_values.append(mappedX)
                y_values.append(mappedY)
                z_values.append(mappedZ)

                # Vẽ điểm
                ax.cla()  # Xóa đồ thị cũ
                ax.set_xlim(0, 200)  # Giới hạn x
                ax.set_ylim(0, 200)  # Giới hạn y
                ax.set_zlim(0, 200)  # Giới hạn z
                ax.scatter(x_values, y_values, z_values)  # Vẽ điểm
                plt.draw()
                plt.pause(0.1)  # Dừng một chút để cập nhật đồ thị

            except ValueError:
                print("Dữ liệu không hợp lệ:", line)

ser.close()
