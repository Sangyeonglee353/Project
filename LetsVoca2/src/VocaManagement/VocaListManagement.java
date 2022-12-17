//package VocaManagement;
//
//import javax.swing.*;
//import java.awt.*;
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//
//import javax.swing.border.EmptyBorder;
//
//import MainDisplay.MainDisplay;
//
//public class VocaListManagement extends JFrame{
//	public VocaListManagement(){
//		
//		// # 0. 기본 셋팅
//		setTitle("이젠 해!! VOCA");
//		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//		Container ctPane = getContentPane(); 
//		ctPane.setLayout(null);
//		
//		Color[] color= {new Color(97, 192, 191), new Color(208, 206, 206)};
//		
//		ImageIcon a2 = new ImageIcon("images/aaa.jpg");
//		
//		// # 1. 폰트 설정
//		Font headerFont = new Font("맑은 고딕", Font.BOLD, 20);
//		
//		// # 2. 상단 제목
//		// # 2-1. 상단 검은색 패널
//		// 검은색 패널(홈 버튼)
//		JPanel header = new JPanel();
//		header.setLocation(0,0);
//		header.setSize(420,50);
//		header.setBackground(Color.BLACK);
//
//		// # 2-2. 상단 제목
//		JLabel headerTitle = new JLabel("단어장 관리");
//		//headerTitle.setHorizontalAlignment(JLabel.CENTER); //JLabel 가운데 정렬
//		headerTitle.setLocation(145, -25);
//		headerTitle.setSize(130,100);
//		headerTitle.setFont(headerFont);
//		headerTitle.setForeground(Color.WHITE);
//		
//		// # 2-3. Home 버튼
//		JButton homeButton = new JButton(new ImageIcon("Images/home.png"));
//		homeButton.setLocation(10,5);
//		homeButton.setBackground(Color.BLACK);
//		homeButton.setSize(42,42);
//		homeButton.setBorderPainted(false);
//		homeButton.setFocusPainted(false);
//		
//		// Home 버튼 이벤트 추가
//		homeButton.addActionListener(new ActionListener() {
//			@Override
//			public void actionPerformed(ActionEvent e) {
//				// 1. 메인페이지로 이동하기
//				new MainDisplay();
//				setVisible(false); // 해당 창 안보이기
//			}
//		});
//		
//		JLabel a3 = new JLabel(a2);
//	    a3.setBounds(0, 0, 420, 50);
//	    
//	    //생성
//	    ImageIcon h2 = new ImageIcon("Images/aaa.PNG");   
//	    JLabel aa = new JLabel(new ImageIcon("Images/pppp.png"));
//	    JButton h4 = new JButton(h2);
//	    JButton h5 = new JButton(h2);
//	    JButton h6 = new JButton(h2);
//	    JButton h7 = new JButton(h2);
//	    JButton h8 = new JButton(h2);
//	    JButton b1 = new JButton("단어장 1");
//	    JButton b2 = new JButton("단어장 2");	    
//        JButton b3 = new JButton("단어장 3");	    
//        JButton b4 = new JButton("단어장 4");
//        JButton b5 = new JButton("단어장 5");       
//        JButton b6 = new JButton("단어장 6");        
//        JButton b7 = new JButton("+");
//	    JLabel h1 = new JLabel(new ImageIcon("Images/aaa.PNG"));       
//	    JButton h3 = new JButton(h2);      
//        
//
//	    EmptyBorder q1 = new EmptyBorder(5,3,5,3);
//	    h3.setBorder(q1);
//	    
//
//        //배경색
//	    h3.setBackground(Color.WHITE);
//	    h4.setBackground(Color.WHITE);
//	    h5.setBackground(Color.WHITE);
//	    h6.setBackground(Color.WHITE);
//	    h7.setBackground(Color.WHITE);
//	    h8.setBackground(Color.WHITE);
//	    b1.setBackground(color[0]);
//	    b2.setBackground(color[0]);
//	    b3.setBackground(color[0]);
//	    b4.setBackground(color[0]);
//	    b5.setBackground(color[0]);
//	    b6.setBackground(color[0]);
//	    b7.setBackground(color[1]);
//	    
//	    //테두리
//	    h4.setBorder(q1);
//	    h5.setBorder(q1);
//	    h6.setBorder(q1);
//	    h7.setBorder(q1);
//	    h8.setBorder(q1);
//	    
//	    //글자색
//	    b1.setForeground(Color.WHITE);
//	    b2.setForeground(Color.WHITE);
//	    b3.setForeground(Color.WHITE);
//	    b4.setForeground(Color.WHITE);
//	    b5.setForeground(Color.WHITE);
//	    b6.setForeground(Color.WHITE);
//	    b7.setForeground(Color.WHITE);
//	    
//	    
//	    //크기, 위치
//	    aa.setBounds(0, 0, 60, 60);	 
//	    h1.setBounds(30, 75, 300, 45);	   
//	    h3.setBounds(330, 130, 55, 55);	
//	    h4.setBounds(330, 185, 55, 55);	         
//	    h5.setBounds(330, 240, 55, 55);	     
//	    h6.setBounds(330, 295, 55, 55);	 
//	    h7.setBounds(330, 350, 55, 55);	      
//	    h8.setBounds(330, 405, 55, 55);	        
//	    b1.setBounds(30, 130, 300, 45);
//        b2.setBounds(30, 185, 300, 45);
//        b3.setBounds(30, 240, 300, 45);
//        b4.setBounds(30, 295, 300, 45);
//        b5.setBounds(30, 350, 300, 45);
//        b6.setBounds(30, 405, 300, 45);
//        b7.setBounds(30, 460, 350, 45);
//        
//        // 컨탠트 팬에 추가
//        ctPane.add(headerTitle);
//        ctPane.add(header);
//        ctPane.add(homeButton);
//        add(h1);
//        add(h3);
//        add(h4);
//        add(h5);
//        add(h6);
//        add(h7);
//        add(h8);
//        add(b1);
//        add(b2);
//        add(b3);
//        add(b4);
//        add(b5);
//        add(b6);
//        add(b7);
//        
//        ctPane.setBackground(Color.WHITE); // 배경색 설정
//		setSize(420, 550); // 프레임 크기
//		setResizable(false); // 창의 크기를 변경하지 못하도록 설정
//		setVisible(true); // 프레임 화면 출력
//	}
//
//	public static void main(String[] argv) {
//		new VocaListManagement();
//		}
//	}

package VocaManagement;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.border.EmptyBorder;

public class VocaListManagement extends JFrame{
	public VocaListManagement(){
		JFrame Frame = new JFrame();
		JFrame Frame1 = new JFrame(); 
		JFrame Frame2 = new JFrame();
		JFrame Frame3 = new JFrame();
		JFrame Frame5 = new JFrame(); 
		JFrame Frame6 = new JFrame();
		JFrame Frame7 = new JFrame();
		JFrame Frame8 = new JFrame();
		
		//반투명 프레임
		JFrame Frame4 = new JFrame();
		Frame4.setUndecorated(true);
		Frame4.setBackground(new Color(0,0,0,122));
	    Frame4.setBounds(0, 0, 420, 550);	
		
		Color color[]= {new Color(187,222,214), new Color(97, 192, 191)};
		
		Container container = Frame.getContentPane();
		Container container1 = Frame1.getContentPane();
		Container container2 = Frame2.getContentPane();
		Container container3 = Frame3.getContentPane();
		Container container4 = Frame5.getContentPane();
		Container container5 = Frame6.getContentPane();
		Container container6 = Frame7.getContentPane();
		Container container7 = Frame8.getContentPane();
		
	    Font font = new Font("맑은 고딕", Font.BOLD, 30);
	    Font font1 = new Font("맑은 고딕", Font.BOLD, 20);

	    Frame.setTitle("나만의 단어장");
		Frame.setSize(420,550);
	    
	    Frame1.setTitle("나만의 단어장");
		Frame1.setSize(420,550);
	    
	    Frame2.setSize(350,405);	   
	    Frame2.setTitle("단어장 수정");
	    
	    Frame3.setSize(300,150);	   
	    Frame3.setTitle("안내");	   
	    
	    Frame5.setTitle("나만의 단어장");
	    Frame5.setSize(420,550);
	    
	    Frame6.setSize(350,405);	   
	    Frame6.setTitle("단어장 수정");
	    
	    Frame7.setSize(300,150);	   
	    Frame7.setTitle("안내");	  
	    
	    Frame8.setSize(300,150);	   
	    Frame8.setTitle("안내");	 
	    
	    setDefaultCloseOperation(EXIT_ON_CLOSE);
	    Frame.setLayout(null);
	    Frame1.setLayout(null);
	    Frame2.setLayout(null);
	    Frame3.setLayout(null);
	    Frame5.setLayout(null);
	    Frame6.setLayout(null);
	    Frame7.setLayout(null);
	    Frame8.setLayout(null);
	    
	    JLabel myNote = new JLabel("나만의 단어장");
	    myNote.setFont(font); 
	    myNote.setOpaque(true);
	    myNote.setBackground(Color.BLACK);
	    myNote.setForeground(Color.WHITE);
        myNote.setHorizontalAlignment(JLabel.CENTER); //JLabel 가운데 정렬
	    myNote.setBounds(0, 0, 420, 60);
	    
	    JLabel myNote_Frame1 = new JLabel("단어장 1");
	    
	    myNote_Frame1.setFont(font);
	    myNote_Frame1.setOpaque(true);
	    myNote_Frame1.setBackground(Color.BLACK);
	    myNote_Frame1.setForeground(Color.WHITE);
	    myNote_Frame1.setHorizontalAlignment(JLabel.CENTER); //JLabel 가운데 정렬
	    
	    //Frame - 생성
	    ImageIcon imageMin = new ImageIcon("images/min.PNG");   
	    JLabel imageHome = new JLabel(new ImageIcon("images/home.PNG"));
	    JButton min1 = new JButton(imageMin);
	    JButton min2 = new JButton(imageMin);
	    JButton min3 = new JButton(imageMin);
	    JButton min4 = new JButton(imageMin);
	    JButton min5 = new JButton(imageMin);
	    JButton min6 = new JButton(imageMin);    
	    JButton note1 = new JButton("단어장 1");
	    JButton note2 = new JButton("단어장 2");	    
        JButton note3 = new JButton("단어장 3");	    
        JButton note4 = new JButton("단어장 4");
        JButton note5 = new JButton("단어장 5");       
        JButton note6 = new JButton("단어장 6");        
        JButton plus = new JButton("+");
	    JTextField search = new JTextField();  
	    JButton searchButton = new JButton(new ImageIcon("images/search.PNG"));
	    
	    //JFrame2 - 생성
	    ImageIcon imageMin_Frame1 = new ImageIcon("images/min.PNG");   
	    JLabel imageHome_Frame1 = new JLabel(new ImageIcon("images/home.PNG"));
	    JButton min1_Frame1 = new JButton(imageMin);
	    JButton min2_Frame1 = new JButton(imageMin);
	    JButton min3_Frame1 = new JButton(imageMin);
	    JButton min4_Frame1 = new JButton(imageMin);
	    JButton min5_Frame1 = new JButton(imageMin);
	    JButton min6_Frame1 = new JButton(imageMin);    
	    JButton english1 = new JButton("Introduce");
	    JButton english2 = new JButton("Education");	    
        JButton english3 = new JButton("Apple");	    
        JButton english4 = new JButton("Banana");
        JButton english5 = new JButton("Cat");       
        JButton english6 = new JButton("Chair");    
	    JButton korean1 = new JButton("소개하다");
	    JButton korean2 = new JButton("교육, 교육기관");	    
        JButton korean3 = new JButton("사과");	    
        JButton korean4 = new JButton("바나나");
        JButton korean5 = new JButton("고양이");       
        JButton korean6 = new JButton("의자");    
        JButton plus_Frame1 = new JButton("+");
	    JTextField search_Frame1 = new JTextField();  
	    JButton searchButton_Frame1 = new JButton(new ImageIcon("images/search.PNG"));   	
	    
	    //JFrame2 - 생성
	    JLabel appleEng = new JLabel("영문 표기 : ");
	    JLabel appleKor = new JLabel("단어 뜻 : ");
	    JLabel image = new JLabel("대표 사진(url 링크) : ");
	    JLabel link = new JLabel("link");
	    JButton enroll = new JButton("등록");
	    JButton cancel = new JButton("취소");
	    JTextField appleEngText = new JTextField();
	    JTextField  appleKorText= new JTextField();
	    JTextField linkText = new JTextField();
  
	    //JFrame3 - 생성
	    JLabel modifyText = new JLabel("<html>단어 등록에 실패하였습니다.<br>다시시도 해주세요.<html>");
	    JButton identifyButton = new JButton("확인");
	    
	    //Frame5 - 생성
	    JLabel imageHome_Frame5 = new JLabel(new ImageIcon("images/home.PNG"));
	    JLabel appleImage = new JLabel(new ImageIcon("images/apple.PNG"));
	    JButton note = new JButton("단어장 1");
	    JTextField search_Frame5 = new JTextField("Apple");       
	    JButton buttionsearch_Frame5 = new JButton(new ImageIcon("images/search.PNG"));
	    JLabel apple = new JLabel("사과");
	    apple.setFont(font);
	    JLabel myNote_Frame5 = new JLabel("나만의 단어장");
	    myNote_Frame5.setOpaque(true);
	    
	    //JFrame6 - 생성
	    JLabel appleEng_Frame6 = new JLabel("영문 표기 : ");
	    JLabel appleKor_Frame6 = new JLabel("단어 뜻 : ");
	    JLabel image_Frame6 = new JLabel("대표 사진(url 링크) : ");
	    JLabel link_Frame6 = new JLabel("link");
	    JButton modify_Frame6 = new JButton("수정");
	    JButton cancel_Frame6 = new JButton("취소");
	    JTextField appleEngText_Frame6 = new JTextField("Apple");
	    JTextField  appleKorText_Frame6 = new JTextField("사과");
	    JTextField linkText_Frame6 = new JTextField("link");
	    
	    //JFrame7 - 생성
	    JLabel modifyText_Frame7 = new JLabel("단어가 수정되었습니다.");
	    JButton identifyButton_Frame7 = new JButton("확인");
	    
	    //JFrame8 - 생성
	    JLabel modifyText_Frame8 = new JLabel("단어가 등록되었습니다.");
	    JButton identifyButton_Frame8 = new JButton("확인");

	    EmptyBorder q1 = new EmptyBorder(5,3,5,3);
	    min6.setBorder(q1);          
	    
        //Frame - 배경색
	    min6.setBackground(Color.WHITE);
	    min1.setBackground(Color.WHITE);
	    min2.setBackground(Color.WHITE);
	    min3.setBackground(Color.WHITE);
	    min4.setBackground(Color.WHITE);
	    min5.setBackground(Color.WHITE);
	    note1.setBackground(color[1]);
	    note2.setBackground(color[1]);
	    note3.setBackground(color[1]);
	    note4.setBackground(color[1]);
	    note5.setBackground(color[1]);
	    note6.setBackground(color[1]);
	    plus.setBackground(new Color(208, 206, 206));
	    searchButton.setBackground(Color.WHITE);
	    
        //JFrame1 - 배경색
		container.setBackground(Color.WHITE);
	    min6_Frame1.setBackground(Color.WHITE);
	    min1_Frame1.setBackground(Color.WHITE);
	    min2_Frame1.setBackground(Color.WHITE);
	    min3_Frame1.setBackground(Color.WHITE);
	    min4_Frame1.setBackground(Color.WHITE);
	    min5_Frame1.setBackground(Color.WHITE);
	    english1.setBackground(color[0]);
	    english2.setBackground(color[0]);
	    english3.setBackground(color[0]);
	    english4.setBackground(color[0]);
	    english5.setBackground(color[0]);
	    english6.setBackground(color[0]);
	    korean1.setBackground(color[0]);
	    korean2.setBackground(color[0]);
	    korean3.setBackground(color[0]);
	    korean4.setBackground(color[0]);
	    korean5.setBackground(color[0]);
	    korean6.setBackground(color[0]);
	    plus_Frame1.setBackground(new Color(208, 206, 206));
	    searchButton_Frame1.setBackground(Color.WHITE);
	    
	    //JFrame2 - 배경색
		container1.setBackground(Color.WHITE);
		enroll.setBackground(new Color(112, 173, 71));
		cancel.setBackground(new Color(47, 85, 151));
		
	    //JFrame3 - 배경색
		container2.setBackground(Color.WHITE);
		identifyButton.setBackground(new Color(112, 173, 71));
		
		//JFrame5 - 배경색
		container4.setBackground(Color.WHITE);
		
        //Frame5 - 배경색
	    note.setBackground(new Color(97, 192, 191));
	    buttionsearch_Frame5.setBackground(Color.WHITE);
	    myNote_Frame5.setBackground(Color.BLACK);
	    
	    //JFrame - 배경색
		container.setBackground(Color.WHITE);
	    min6.setBackground(Color.WHITE);
	    min1.setBackground(Color.WHITE);
	    min2.setBackground(Color.WHITE);
	    min3.setBackground(Color.WHITE);
	    min4.setBackground(Color.WHITE);
	    min5.setBackground(Color.WHITE);
	    english1.setBackground(color[0]);
	    english2.setBackground(color[0]);
	    english3.setBackground(color[0]);
	    english4.setBackground(color[0]);
	    english5.setBackground(color[0]);
	    english6.setBackground(color[0]);
	    korean1.setBackground(color[0]);
	    korean2.setBackground(color[0]);
	    korean3.setBackground(color[0]);
	    korean4.setBackground(color[0]);
	    korean5.setBackground(color[0]);
	    korean6.setBackground(color[0]);
	    plus.setBackground(new Color(208, 206, 206));
	    searchButton.setBackground(Color.WHITE);
	    
	    //JFrame6 - 배경색
		container5.setBackground(Color.WHITE);
		modify_Frame6.setBackground(new Color(112, 173, 71));
		cancel_Frame6.setBackground(new Color(47, 85, 151));
		
	    //JFrame7 - 배경색
		container6.setBackground(Color.WHITE);
		identifyButton_Frame7.setBackground(new Color(112, 173, 71));
		
	    //JFrame8 - 배경색
		container7.setBackground(Color.WHITE);
		identifyButton_Frame8.setBackground(new Color(112, 173, 71));
	    
	    //테두리
	    min1.setBorder(q1);
	    min2.setBorder(q1);
	    min3.setBorder(q1);
	    min4.setBorder(q1);
	    min5.setBorder(q1);
	    searchButton.setBorder(q1);
	    min1_Frame1.setBorder(q1);
	    min2_Frame1.setBorder(q1);
	    min3_Frame1.setBorder(q1);
	    min4_Frame1.setBorder(q1);
	    min5_Frame1.setBorder(q1);
	    min6_Frame1.setBorder(q1);;
	    searchButton_Frame1.setBorder(q1);
	    
	    //Frame5 - 테두리
	    buttionsearch_Frame5.setBorder(q1);
	    
	    //글자색
	    //Frame - 글자색
	    note1.setForeground(Color.WHITE);
	    note2.setForeground(Color.WHITE);
	    note3.setForeground(Color.WHITE);
	    note4.setForeground(Color.WHITE);
	    note5.setForeground(Color.WHITE);
	    note6.setForeground(Color.WHITE);
	    plus.setForeground(Color.WHITE);
	    
	    //JFrame2 - 글자색
	    enroll.setForeground(Color.WHITE);
	    cancel.setForeground(Color.WHITE);
	    
	    //JFrame3 - 글자색
	    identifyButton.setForeground(Color.WHITE);
	    
	    //Frame5 - 글자색
	    note.setForeground(Color.WHITE);
	    myNote_Frame5.setForeground(Color.WHITE);
	    
	    //JFrame6 - 글자색
	    modify_Frame6.setForeground(Color.WHITE);
	    cancel_Frame6.setForeground(Color.WHITE);
	    
	    //JFrame7 - 글자색
	    identifyButton_Frame7.setForeground(Color.WHITE);
	    
	    //JFrame8 - 글자색
	    identifyButton_Frame8.setForeground(Color.WHITE);
	    
	    //Frame - 크기, 위치
	    imageHome.setBounds(0, 0, 60, 60);	 
	    search.setBounds(80, 75, 250, 45);	 
	    searchButton.setBounds(330, 75, 45, 45);
	    min6.setBounds(330, 130, 55, 55);	
	    min1.setBounds(330, 185, 55, 55);	         
	    min2.setBounds(330, 240, 55, 55);	     
	    min3.setBounds(330, 295, 55, 55);	 
	    min4.setBounds(330, 350, 55, 55);	      
	    min5.setBounds(330, 405, 55, 55);	        
	    note1.setBounds(30, 130, 300, 45);
        note2.setBounds(30, 185, 300, 45);
        note3.setBounds(30, 240, 300, 45);
        note4.setBounds(30, 295, 300, 45);
        note5.setBounds(30, 350, 300, 45);
        note6.setBounds(30, 405, 300, 45);
        plus.setBounds(30, 460, 350, 45);
	    
	    //JFrame1 - 위치, 크기
	    imageHome_Frame1.setBounds(0, 0, 60, 60);	
	    myNote_Frame1.setBounds(0, 0, 420, 50);
	    search_Frame1.setBounds(80, 70, 250, 45);	 
	    searchButton_Frame1.setBounds(330, 70, 45, 45);
        korean1.setBounds(180, 125, 140, 45);
	    english1.setBounds(30, 125, 140, 45);
	    min1_Frame1.setBounds(330, 125, 55, 55);	
        korean2.setBounds(180, 180, 140, 45);
        english2.setBounds(30, 180, 140, 45);
        min2_Frame1.setBounds(330, 180, 55, 55);
        korean3.setBounds(180, 235, 140, 45);
        english3.setBounds(30, 235, 140, 45);
	    min3_Frame1.setBounds(330, 235, 55, 55);	
        korean4.setBounds(180, 290, 140, 45);
        english4.setBounds(30, 290, 140, 45);  
	    min4_Frame1.setBounds(330, 290, 55, 55);	
        korean5.setBounds(180, 345, 140, 45);
        english5.setBounds(30, 345, 140, 45);
	    min5_Frame1.setBounds(330, 345, 55, 55);	  
        korean6.setBounds(180, 400, 140, 45);
        english6.setBounds(30, 400, 140, 45);
	    min6_Frame1.setBounds(330, 400, 55, 55);	 
        plus_Frame1.setBounds(30, 455, 350, 45);
	    
	    //JFrame2 - 위치, 크기
	    Frame2.setBounds(35,90,350,420);
	    appleEng.setBounds(10,30,110,35);
	    appleKor.setBounds(10, 110, 110, 35);
	    image.setBounds(10, 180, 220, 35);
        appleEngText.setBounds(140, 30, 180, 35);
        appleKorText.setBounds(140, 110, 180, 35);
	    linkText.setBounds(15, 215, 295, 35);
	    enroll.setBounds(40, 295, 120, 40);
	    cancel.setBounds(180, 295, 120, 40);
	    
	    //JFrame3 - 위치, 크기
	    Frame3.setBounds(60 , 200, 300, 150);
	    modifyText.setBounds(20, 0, 260, 60);
	    identifyButton.setBounds(90, 50, 100, 40);
	    
	    //Frame5 - 위치, 크기
	    imageHome_Frame5.setBounds(0, 0, 60, 60);	 
	    search_Frame5.setBounds(80, 75, 250, 45);	 
	    buttionsearch_Frame5.setBounds(330, 75, 45, 45);       
	    note.setBounds(50, 130, 300, 45);
	    apple.setBounds(170, 190, 70, 70);
	    appleImage.setBounds(65,255,260,165);
	    myNote_Frame5.setBounds(0, 0, 420, 60);
	    
	    //JFrame6 - 위치, 크기
	    Frame6.setBounds(35,90,350,420);
	    appleEng_Frame6.setBounds(10,30,110,35);
	    appleKor_Frame6.setBounds(10, 110, 110, 35);
	    image_Frame6.setBounds(10, 180, 220, 35);
        appleEngText_Frame6.setBounds(140, 30, 180, 35);
        appleKorText_Frame6.setBounds(140, 85, 180, 35);
	    linkText_Frame6.setBounds(10, 215, 300, 35);
	    modify_Frame6.setBounds(40, 295, 120, 40);
	    cancel_Frame6.setBounds(180, 295, 120, 40);
	    
	    //JFrame7 - 위치, 크기
	    Frame7.setBounds(60 , 200, 300, 150);
	    modifyText_Frame7.setBounds(20, 0, 260, 60);
	    identifyButton_Frame7.setBounds(90, 50, 100, 40);
	    
	    //JFrame8 - 위치, 크기
	    Frame8.setBounds(60 , 200, 300, 150);
	    modifyText_Frame8.setBounds(20, 0, 260, 60);
	    identifyButton_Frame8.setBounds(90, 50, 100, 40);
	    
        //Frame - 폰트
	    search.setFont(new Font("궁서 보통", Font.BOLD, 20));
        search.setHorizontalAlignment(JLabel.CENTER); //JLabel 가운데 정렬
	    
        //JFrame2 - 폰트
	    appleEng.setFont(font1);
	    appleKor.setFont(font1);
	    image.setFont(font1);
	    appleEngText.setFont(font1);
	    appleKorText.setFont(font1);
	    linkText.setFont(font1);
	    appleEngText.setHorizontalAlignment(JLabel.CENTER);
	    appleKorText.setHorizontalAlignment(JLabel.CENTER);
	    
        //Frame5 - 폰트
	    search_Frame5.setFont(new Font("궁서 보통", Font.BOLD, 20));
        search_Frame5.setHorizontalAlignment(JLabel.CENTER); //JLabel 가운데 정렬
        myNote_Frame5.setHorizontalAlignment(JLabel.CENTER); //JLabel 가운데 정렬
	    myNote_Frame5.setFont(font);
	    
        //JFrame6 - 폰트
	    appleEng_Frame6.setFont(font1);
	    appleKor_Frame6.setFont(font1);
	    image_Frame6.setFont(font1);
	    appleEngText_Frame6.setFont(font1);
	    appleKorText_Frame6.setFont(font1);
	    linkText_Frame6.setFont(font1);
	    
	    //Frame7 - 폰트
	    modifyText_Frame7.setFont(font1);
	    
	    //Frame8 - 폰트
	    modifyText_Frame8.setFont(font1);
	    
	    
	    //JFrame2 - 가운데 정렬
	    appleEngText.setHorizontalAlignment(JLabel.CENTER); // 가운데 정렬
	    appleKorText.setHorizontalAlignment(JLabel.CENTER);
	    
	    //JFrame3 - 가운데 정렬
	    modifyText.setHorizontalAlignment(JLabel.CENTER);
	    
	    //JFrame6 - 가운데 정렬
	    appleEngText_Frame6.setHorizontalAlignment(JLabel.CENTER);
	    appleKorText_Frame6.setHorizontalAlignment(JLabel.CENTER);
	    
	    //JFrame7 - 가운데 정렬
	    modifyText_Frame7.setHorizontalAlignment(JLabel.CENTER);

	    //JFrame8 - 가운데 정렬
	    modifyText_Frame8.setHorizontalAlignment(JLabel.CENTER);
	    
        //Frame - 추가
        Frame.add(imageHome);
        Frame.add(myNote);
        Frame.add(search);
        Frame.add(min1);
        Frame.add(min2);
        Frame.add(min3);
        Frame.add(min4);
        Frame.add(min5);
        Frame.add(min6);
        Frame.add(note1);
        Frame.add(note2);
        Frame.add(note3);
        Frame.add(note4);
        Frame.add(note5);
        Frame.add(note6);
        Frame.add(plus);
        Frame.add(searchButton);
        Frame.setVisible(true);

        //JFrame1 - 추가
        Frame1.add(imageHome_Frame1);
        Frame1.add(myNote_Frame1);
        Frame1.add(search_Frame1);
        Frame1.add(min6_Frame1);
        Frame1.add(min1_Frame1);
        Frame1.add(min2_Frame1);
        Frame1.add(min3_Frame1);
        Frame1.add(min4_Frame1);
        Frame1.add(min5_Frame1);
        Frame1.add(english1);
        Frame1.add(english2);
        Frame1.add(english3);
        Frame1.add(english4);
        Frame1.add(english5);
        Frame1.add(english6);
        Frame1.add(korean1);
        Frame1.add(korean2);
        Frame1.add(korean3);
        Frame1.add(korean4);
        Frame1.add(korean5);
        Frame1.add(korean6);
        Frame1.add(plus_Frame1);
        Frame1.add(searchButton_Frame1);
        
        //JFrame2 - 추가
        Frame2.add(appleEng);
        Frame2.add(appleKor);
        Frame2.add(image);
        Frame2.add(link);
        Frame2.add(enroll);
        Frame2.add(cancel);
        Frame2.add(appleEngText);
        Frame2.add(appleKorText);
        Frame2.add(linkText);
        
        //반투명 프레임 추가
//      Frame4.setVisible(true);
        
        //Frame3 - 추가
        Frame3.add(identifyButton);
        Frame3.add(modifyText);        
        
        //Frame5 - 추가
        Frame5.add(imageHome_Frame5);
        Frame5.add(myNote_Frame5);
        Frame5.add(search_Frame5);
        Frame5.add(note);
        Frame5.add(buttionsearch_Frame5);
        Frame5.add(apple);
        Frame5.add(appleImage);	
        
        //JFrame6 - 추가
        Frame6.add(appleEng_Frame6);
        Frame6.add(appleKor_Frame6);
        Frame6.add(image_Frame6);
        Frame6.add(link_Frame6);
        Frame6.add(modify_Frame6);
        Frame6.add(cancel_Frame6);
        Frame6.add(appleEngText_Frame6);
        Frame6.add(appleKorText_Frame6);
        Frame6.add(linkText_Frame6);
        
        //Frame7 - 추가
        Frame7.add(identifyButton_Frame7);
        Frame7.add(modifyText_Frame7);
        
        //Frame8 - 추가
        Frame8.add(identifyButton_Frame8);
        Frame8.add(modifyText_Frame8);      
        
		note1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
		        Frame.setVisible(false);
		        Frame1.setVisible(true);
			}
		});
        
		korean1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Frame4.setVisible(true);
		        Frame6.setVisible(true);
			}
		});
		
		english1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Frame4.setVisible(true);
		        Frame6.setVisible(true);
			}
		});
		
		cancel_Frame6.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Frame4.setVisible(false);
		        Frame6.setVisible(false);
			}
		});
		
		modify_Frame6.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Frame4.setVisible(true);
				Frame7.setVisible(true);
			}
		});
		
		identifyButton_Frame7.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Frame4.setVisible(false);
				Frame7.setVisible(false);
			}
		});
        
		plus_Frame1.addActionListener(new ActionListener() {	// note1을 눌렀을 때 효과추가
			public void actionPerformed(ActionEvent e) {
				Frame4.setVisible(true);
		        Frame2.setVisible(true);
			}
		});
		
		enroll.addActionListener(new ActionListener() {	// note1을 눌렀을 때 효과추가
			public void actionPerformed(ActionEvent e) {
				Frame4.setVisible(true);
		        Frame8.setVisible(true);
			}
		});

		identifyButton_Frame8.addActionListener(new ActionListener() {	// note1을 눌렀을 때 효과추가
			public void actionPerformed(ActionEvent e) {
				Frame4.setVisible(false);
		        Frame8.setVisible(false);
		        Frame2.setVisible(false);
			}
		});
		
		cancel.addActionListener(new ActionListener() {	// note1을 눌렀을 때 효과추가
			public void actionPerformed(ActionEvent e) {
				Frame4.setVisible(false);
		        Frame2.setVisible(false);
			}
		});
		
	}
	
	
	public static void main(String[] argv) {
		new VocaListManagement();
		}
	}


