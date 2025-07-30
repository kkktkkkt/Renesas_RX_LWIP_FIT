# -*- coding: utf-8 -*-
import socket

# --- 設定 ---
HOST = '192.168.11.20'  # Sever Ip address
PORT = 12345        # Listen Port (Recommend : upper 1024)
BUFFER_SIZE = 1024  # Muximum size of data to receive at once

def main():
    # 1. socket creation
    #    - socket.AF_INET: using IPv4
    #    - socket.SOCK_DGRAM: using UDP protocol
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        
        # 2. set Host IP and Port
        s.bind((HOST, PORT))
        print(f"UDP Echo Server {HOST}:{PORT} running...")

        try:
            # 3. Waiting for receive message
            while True:
                # Receive data from client
                data, client_address = s.recvfrom(BUFFER_SIZE)
                
                # Decode the received data
                message = data.decode('utf-8')
                print(f"Client {client_address} : message : {message}")

                # 4. Send the same data back to the client
                s.sendto(data, client_address)
                print(f"Client {client_address} : message replied")

        except KeyboardInterrupt:
            # Ctrl+C が押されたらサーバーを停止
            print("\nShoutting down the server...")

if __name__ == '__main__':
    main()