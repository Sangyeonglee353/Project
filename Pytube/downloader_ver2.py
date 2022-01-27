# call lib
from tkinter import *
from tkinter import messagebox # 메시지 박스
from tkinter import filedialog # 경로 지정
from pytube import YouTube
from moviepy.editor import * # 영상과 오디오 결합
import glob
import os.path
import tkinter.ttk as ttk

# set
root = Tk()
root.title("Youtube converter")
root.geometry("500x700")
root.resizable(False, False)

# [기능 구현]
# 변환 주소 추가
def add_lnk():
	par = lnk.get() # 주소 가져오기
	if len(par) == 0:
		messagebox.showwarning("경고", "주소를 입력해주세요.")
		return
	list_lnk.insert(END, par)

# 선택 삭제
def del_lnk():
	for index in reversed(list_lnk.curselection()):
		list_lnk.delete(index)

# convert
def convert():
	# 유튜브 주소 → 파일 변환
	# par = lnk.get() # 주소 가져오기
	dest_path = txt_dest_path.get() # 저장경로 가져오기

	lnks = list_lnk.get(0, END) # 변환 주소 목록 가져오기
	#print(list_lnk.get(0, END))
	# print(par)
	print("start!")

	for idx, par in enumerate(lnks):
		yt = YouTube(par)	

		if(Radiovar.get() == 1):
			print("type: mp4")
			yt.streams.filter().all() # 다운가능한 형태 목록 모든 값 리스트로 반환
			print("다운가능한 영상 상세 정보 :")
			for i, stream in enumerate(yt.streams.all()):
				print(i, " : ", stream)

			print(" 고화질, mp4 포맷만 가져오기 : ")
			for i, stream in enumerate(yt.streams.filter(adaptive=True, file_extension='mp4').all()):
				print(i, " : ", stream)

			# 유튜브는 mp4파일을 동영상과 오디오로 분리해서 제공하고 있다. 따라서 이 둘을 받아서 합쳐야 함.
			
			# 0. 파일명
			title = yt.title

			# 1. 동영상
			# order_by("resolution").desc().first()는 변환 가능한 영상 화질 중 가장 높은 화질을 대상으로 선택
			yt.streams.filter(adaptive=True, file_extension='mp4', only_video=True).order_by('resolution').desc().first().download(dest_path, title+'video.mp4') 

			# 2. 오디오
			# order_by("abr").desc().first()는 변환 가능한 영상 화질 중 가장 좋은 음질을 대상으로 선택
			yt.streams.filter(adaptive=True, file_extension='mp4', only_audio=True).order_by('abr').desc().first().download(dest_path, title+'audio.mp4') 
			print(yt.title)
			
			# 3. 동영상 + 오디오 합치기
			video_addr = [dest_path,'/',title,'video.mp4']
			audio_addr = [dest_path,'/',title,'audio.mp4']
			video_file = "".join(video_addr)
			audio_file = "".join(audio_addr)
			videoclip = VideoFileClip(video_file)
			audioclip = AudioFileClip(audio_file)

			# 3-1. 오디오 파일 가져오기
			videoclip.audio = audioclip

			# 3-2. 이 오디오 파일에 동영상을 합쳐 완전한 소리가 나오는 동영상 파일을 만든다.
			videoclip.write_videofile(dest_path+'/'+title+'.mp4')

			# 3-3. 필요없는 동영상 파일과 오디오 파일을 삭제한다.
			os.remove(video_file)
			os.remove(audio_file)
		else:
			print("type: mp3")
			yt.streams.filter(only_audio=True).all()
			print("다운가능한 영상 상세 정보 :")
			for i, stream in enumerate(yt.streams.all()):
				print(i, " : ", stream)
				
			print("mp3 포맷만 가져오기 : ")
			for i, stream in enumerate(yt.streams.filter(only_audio=True).all()):
				print(i, " : ", stream)
			
			# 오디오 목록 중 첫번째 형식으로 다운로드
			yt.streams.filter(only_audio=True).first().download(dest_path)
			
			# mp3로 확장자 변경
			files = glob.glob("*.mp4") # 현재 문서에서 해당 확장에 해당하는 파일을 가져온다.
			for x in files:
				if not os.path.isdir(x):
					filename = os.path.splitext(x)
					try:
						os.rename(x,filename[0] + '.mp3')
					except:
						pass
			print("success")

		# 진행상황 표시
		progress = (idx + 1) / len(lnks) * 100
		p_var.set(progress)
		progress_bar.update()

	#메시지 박스 표시
	messagebox.showinfo("success","converted!") 

# 저장 경로 (폴더)
def browse_dest_path():
	folder_selected = filedialog.askdirectory()
	if folder_selected == '':
		return
	print(folder_selected)
	txt_dest_path.delete(0, END) # Entry 리스트 삭제
	txt_dest_path.insert(0, folder_selected)

# 시작
def start():
	# 주소 목록 확인
	if list_lnk.size() == 0:
		messagebox.showwarning("경고", "변환 주소를 추가해주세요.")
		return
	
	if len(txt_dest_path.get()) == 0:
		messagebox.showwarning("경고", "저장 경로를 선택해주세요.")
		return
	
	# 변환 작업 시작
	convert()

# 유튜브 주소 프레임
lnk_frame = LabelFrame(root, text="변환 주소")
lnk_frame.pack(fill="x", padx=5, pady=5, ipady=5)

lnk = Entry(lnk_frame)
lnk.pack(side="left", fill="x", expand=True, padx=5, pady=5, ipady=5)

btn_del_lnk = Button(lnk_frame, padx=5, pady=5, width=10, text="선택삭제", command=del_lnk)
btn_del_lnk.pack(side="right", padx=5, pady=5)

btn_add_lnk = Button(lnk_frame, padx=5, pady=5, width=10, text="주소추가", command=add_lnk)
btn_add_lnk.pack(side="right", padx=5, pady=5)

# 리스트 프레임
list_frame = Frame(root)
list_frame.pack(fill="both", padx=5, pady=5)

scrollbar = Scrollbar(list_frame)
scrollbar.pack(side="right", fill="y")

list_lnk = Listbox(list_frame, selectmode="extended", height=15, yscrollcommand=scrollbar.set)
list_lnk.pack(side="left", fill="both", expand=True)
scrollbar.config(command=list_lnk.yview)

# 옵션 프레임
option_frame = LabelFrame(root, text="옵션")
option_frame.pack(fill="x", padx=5, pady=5, ipady=5)

st = StringVar() 
Radiovar = IntVar(value=2) 
Radio_button1 = Radiobutton(option_frame, text="mp4",variable=Radiovar,value=1) 
Radio_button2 = Radiobutton(option_frame, text="mp3",variable=Radiovar,value=2)
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

btn_convert = Button(frame_run, text="변환하기", width=12, command=start)
btn_convert.pack(side="right", padx=5, pady=5)

root.resizable(False, False) # 창 크기 변경 불가
root.mainloop()