import cv2
import serial
import numpy as np

# Kết nối tới cổng COM
ser = serial.Serial('COM15', 57600)  # Thay đổi 'COM15' theo cổng mà Arduino đang kết nối

# Kích thước hình ảnh
width, height = 640, 480

# Tạo một khung hình trắng
frame = np.ones((height, width, 3), dtype=np.uint8) * 255

# Danh sách để lưu trữ các điểm vẽ nét chữ
points = []

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

                # Lưu trữ tọa độ mới vào danh sách
                points.append((int(mappedX), int(mappedY)))

                # Vẽ các nét chữ
                for i in range(1, len(points)):
                    cv2.line(frame, points[i - 1], points[i], (0, 0, 0), 2)  # Vẽ nét nối giữa các điểm

                # Hiển thị khung hình
                cv2.imshow('Drawing with Hand', frame)

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
