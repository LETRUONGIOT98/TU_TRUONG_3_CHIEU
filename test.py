import cv2
import serial
import numpy as np

# Kết nối tới cổng COM
ser = serial.Serial('COM15', 57600)  # Thay đổi 'COM15' theo cổng mà Arduino đang kết nối

# Kích thước hình ảnh
width, height = 640, 480

# Tạo một khung hình trắng
frame = np.ones((height, width, 3), dtype=np.uint8) * 255

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
                mappedX = np.clip(np.interp(xMag, [x_min, x_max], [0, width]), 0, width - 1)
                mappedY = np.clip(np.interp(yMag, [y_min, y_max], [height, 0]), 0, height - 1)  # Lật trục Y
                mappedZ = np.clip(np.interp(zMag, [z_min, z_max], [0, 255]), 0, 255)  # Sử dụng độ sáng cho Z

                # Tạo màu sắc dựa trên tọa độ Z
                color = (int(mappedZ), 0, 255 - int(mappedZ))  # Màu sắc tùy thuộc vào tọa độ Z

                # Vẽ điểm trên khung hình
                cv2.circle(frame, (int(mappedX), int(mappedY)), 5, color, -1)

                # Hiển thị khung hình
                cv2.imshow('3D Points', frame)

                # Nhấn 'q' để thoát
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break

                # Xóa khung hình để vẽ lại
                frame[:] = 255

            except ValueError:
                print("Dữ liệu không hợp lệ:", line)

# Giải phóng tài nguyên
ser.close()
cv2.destroyAllWindows()
