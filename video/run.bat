ffmpeg.exe -i ..\frames\test_%%d.tga -c:v ffv1 -qscale:v 0 video.avi
start video.avi