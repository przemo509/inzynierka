ffmpeg.exe -f image2 -i ..\frames\test_%%d.tga -vcodec mpeg4 -b:v 10000k video.avi
start video.avi