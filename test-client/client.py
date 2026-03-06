
import socket


def main():

  client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

  try:
    client.connect(("127.0.0.1", 7777))
    while True:
    
      data_to_send = input()

      client.send(data_to_send.encode())
  except KeyboardInterrupt:
    print("Shutdown")
    client.close()
  except Exception as e:
    client.close()
    print(e)


if __name__ == "__main__":
  main()