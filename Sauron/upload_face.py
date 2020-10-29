import os
import boto3
from datetime import datetime

timestamp = datetime.now().strftime("%Y_%m_%d_%H:%M:%S")
filename = timestamp+".jpg"

s3 = boto3.resource('s3')

os.chdir("/home/pi/Sauron")

data = open('shot.jpg', 'rb')
s3.Bucket('sauronfaces').put_object(Key=filename, Body=data)
