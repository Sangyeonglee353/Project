# call lib
from tkinter import *
from tkinter import messagebox
from tkinter import filedialog
from pytube import YouTube
import glob
import os.path
import tkinter.ttk as ttk

# set
root = Tk()
root.title("Youtube converter")
root.geometry("500x350")
root.resizable(False, False)

# convert
def convert():
	#유튜브 전용 인스턴스 생성
	par = lnk.get() # 주소 가져오기
	dest_path = txt_dest_path.get() # 저장경로 가져오기
	# print(par)

	yt = YouTube(par)

	print("start!")
	if(Radiovar.get() == 1):
		print("type: mp4")
		yt.streams.filter().all()
		yt.streams.filter().first().download(dest_path) 
	else:
		print("type: mp3")
		# print("타입: {0}".format(type(dest_path)))
		# print("경로: {0}".format(dest_path))
		yt.streams.filter(only_audio=True).all()
		yt.streams.filter(only_audio=True).first().download(dest_path)
		print("success")

		# 확장자 변경
		files = glob.glob("*.mp4") # 현재 문서에서 해당 확장에 해당하는 파일을 가져온다.
		for x in files:
			if not os.path.isdir(x):
				filename = os.path.splitext(x)
				try:
					os.rename(x,filename[0] + '.mp3')
				except:
					pass
	messagebox.showinfo("success","converted!") #메시지 박스를 띄운다.

# 저장 경로 (폴더)
def browse_dest_path():
	folder_selected = filedialog.askdirectory()
	if folder_selected == '':
		return
	print(folder_selected)
	txt_dest_path.delete(0, END) # Entry 리스트 삭제
	txt_dest_path.insert(0, folder_selected)

# 유튜브 주소 프레임
link_frame = LabelFrame(root, text="변환 주소")
link_frame.pack(fill="x", padx=5, pady=5, ipady=5)

lnk = Entry(link_frame)
lnk.pack(fill="x", padx=5, pady=5, ipady=5)

# 옵션 프레임
option_frame = LabelFrame(root, text="옵션")
option_frame.pack(fill="x", padx=5, pady=5, ipady=5)

st = StringVar() 
Radiovar = IntVar() 
Radio_button1 = Radiobutton(option_frame, text="mp4",variable=Radiovar,value=1) 
Radio_button2 = Radiobutton(option_frame, text="mp3(=default)",variable=Radiovar,value=2)
Radio_button1.pack(side="left", padx=5, pady=5, ipady=5)
Radio_button2.pack(padx=5, pady=5, ipady=5)

# 저장 경로 프레임
path_frame = LabelFrame(root, text="저장경로")
path_frame.pack(fill="x", padx=5, pady=5, ipady=5)

txt_dest_path = Entry(path_frame)
txt_dest_path.pack(side="left", fill="x", expand=True, padx=5, pady=5, ipady=4)

btn_dest_path = Button(path_frame, text="찾아보기", width=10, command=browse_dest_path)
btn_dest_path.pack(side="right", padx=5, pady=5)

# 진행 상황
frame_progress = LabelFrame(root, text="진행상황")
frame_progress.pack(fill="x", padx=5, pady=5, ipady=5)

p_var = DoubleVar()
progress_bar = ttk.Progressbar(frame_progress, maximum=100, variable=p_var)
progress_bar.pack(fill="x", padx=5, pady=5)

# 실행 프레임
frame_run = Frame(root)
frame_run.pack(fill="x", padx=5, pady=5)

btn_convert = Button(frame_run, text="종료하기", width=12, command=root.quit)
btn_convert.pack(side="right", padx=5, pady=5)

btn_convert = Button(frame_run, text="변환하기", width=12, command=convert)
btn_convert.pack(side="right", padx=5, pady=5)

root.resizable(False, False) # 창 크기 변경 불가
root.mainloop()