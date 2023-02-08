import cv2
import time
import threading

class VideoCamera(object):
    def __init__(self):
        try:
            self.video = cv2.VideoCapture(0)
            (self.grabbed, self.frame) = self.video.read()
            threading.Thread(target=self.update, args=()).start()
        except Exception as e:
            raise Exception("Camera in use")
    def __del__(self):
        print("released!!\n\n")
        self.video.release()

    def get_frame(self):
        image = self.frame
        _, jpeg = cv2.imencode('.jpg', image)
        return jpeg.tobytes()

    def update(self):
        while True:
            (self.grabbed, self.frame) = self.video.read()

def gen(camera):
    while True:
        try:
            frame = camera.get_frame()
            yield(b'--frame\r\n'
                b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n\r\n')
        except Exception as e:
            raise Exception("Camera in use")



def close_camera(cam, response):
    while response and not response.closed:
        time.sleep(1)
    if cam:
        cam.video.release()
