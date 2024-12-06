#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int len = PA0; int gtlen;  // Nút Lên
int xuong = PA1; int gtxuong; // Nút Xuống
int menu = PA2; int gtmenu;  
int back = PA3; int gtback; 
int macdinh = 1;

int congtru_tong = 0; int congtru_menu1 = 0; int congtru_menu2 = 0; int congtru_mode = 0;
int demmenu1 = 0; int demmenu2 = 0; int chedo = 0;
int demtong = 0;  
int demback = 0;
int setmenu1 = 0; int setmenu2 = 0;
int gtnhietdov1 = 78; 
int gtdoamv1 = 44;
int gtnhietdov2 = 32; 
int gtdoamv2 = 32;
bool chedo_auto = true;
void manhinh()  // HIỂN THỊ MÀN HÌNH CHÍNH
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" MAN HINH CHINH "); 
}

void menu_tong() // HIỂN THỊ MENU TỔNG
{
  if (congtru_tong == 0)
  {
    lcd.clear();
    lcd.print(">VUON 1");
    lcd.setCursor(0, 1);
    lcd.print(" VUON 2");  
  }
  else if (congtru_tong == 1)
  {
    lcd.clear();
    lcd.print(" VUON 1");
    lcd.setCursor(0, 1);
    lcd.print(">VUON 2");    
  }
  else if (congtru_tong == 2)
  {
    lcd.clear();
    lcd.print(">CHE DO");
    lcd.setCursor(0, 1);
    lcd.print(" ");
  }

}
// Xử lý menu1
void menu_1()  // HIỂN THỊ MENU 1
{
  if (congtru_menu1 == 0)
  {
    lcd.clear();
    lcd.print(">THONG TIN V1");
    lcd.setCursor(0, 1);
    lcd.print(" CAI DAT V1");  
  }
  else if (congtru_menu1 == 1)
  {
    lcd.clear();
    lcd.print(" THONG TIN V1");
    lcd.setCursor(0, 1);
    lcd.print(">CAI DAT V1");    
  }   
}

void chonmenu_1() // CHỌN MENU 1
{
  switch (congtru_menu1) 
  {
    case 0:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("NHIET DO V1 ");
      lcd.setCursor(0,1);
      lcd.print("DO AM V1  ");
      break;
    case 1:
      demmenu1 = 1; // Chuyển trạng thái để điều chỉnh
      setmenu1 = 0; // Bắt đầu từ điều chỉnh nhiệt độ
      caidat_menu1(); // Gọi màn hình cài đặt
      break;  
  }
}

void caidat_menu1(){
  lcd.clear();
  if (setmenu1 == 0) { // Điều chỉnh nhiệt độ
    lcd.setCursor(0, 0);
    lcd.print(">Nhiet do: ");
    lcd.print(gtnhietdov1);
    lcd.setCursor(0, 1);
    lcd.print(" Do am: ");
    lcd.print(gtdoamv1);
  } else if (setmenu1 == 1) { // Điều chỉnh độ ẩm
    lcd.setCursor(0, 0);
    lcd.print(" Nhiet do: ");
    lcd.print(gtnhietdov1);
    lcd.setCursor(0, 1);
    lcd.print(">Do am: ");
    lcd.print(gtdoamv1);
  }
}
// Xử lý menu2
void menu_2() // HIỂN THỊ MENU 2
{
  if (congtru_menu2 == 0)
  {
    lcd.clear();
    lcd.print(">THONG TIN V2");
    lcd.setCursor(0, 1);
    lcd.print(" CAI DAT V2");  
  }
  else if (congtru_menu2 == 1)
  {
    lcd.clear();
    lcd.print(" THONG TIN V2");
    lcd.setCursor(0, 1);
    lcd.print(">CAI DAT V2");    
  }  
}

void chonmenu_2() // CHỌN MENU 2
{
  switch (congtru_menu2) 
  {
    case 0:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("NHIET DO V2: ");
      lcd.setCursor(0,1);
      lcd.print("DO AM V2:  ");
      break;
    case 1:
      demmenu2 = 1; // Chuyển trạng thái để điều chỉnh
      setmenu2 = 0; // Bắt đầu từ điều chỉnh nhiệt độ
      caidat_menu2(); // Gọi màn hình cài đặt
      break;  
  }
}

void caidat_menu2(){
  lcd.clear();
  if (setmenu2 == 0) { // Điều chỉnh nhiệt độ
    lcd.setCursor(0, 0);
    lcd.print(">Nhiet do: ");
    lcd.print(gtnhietdov2);
    lcd.setCursor(0, 1);
    lcd.print(" Do am: ");
    lcd.print(gtdoamv2);
  } else if (setmenu2 == 1) { // Điều chỉnh độ ẩm
    lcd.setCursor(0, 0);
    lcd.print(" Nhiet do: ");
    lcd.print(gtnhietdov2);
    lcd.setCursor(0, 1);
    lcd.print(">Do am: ");
    lcd.print(gtdoamv2);
  }
}
void menu_chedo() // HIỂN THỊ MENU "CHẾ ĐỘ"
{
  lcd.clear();
  if (congtru_mode == 0)
  {
    lcd.print(">AUTO");
    lcd.setCursor(0, 1);
    lcd.print(" THU CONG");
  }
  else if (congtru_mode == 1)
  {
    lcd.print(" AUTO");
    lcd.setCursor(0, 1);
    lcd.print(">THU CONG");
  }
}

void chon_chedo() // CHỌN CHẾ ĐỘ
{
  lcd.clear();
  if (congtru_mode == 0) {
    lcd.print("Che do: AUTO");
    chedo = 0;
    chedo_auto = true;
  } else if (congtru_mode == 1) {
    lcd.print("Che do: THU CONG");
    chedo = 1;
    chedo_auto = false;
  }
}

void setup() 
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(len, INPUT_PULLUP);
  pinMode(xuong, INPUT_PULLUP);
  pinMode(menu, INPUT_PULLUP);
  pinMode(back, INPUT_PULLUP);
  manhinh();
}
unsigned long lastDebounceTime = 0; // Thời gian debounce
const unsigned long debounceDelay = 200; // Độ trễ debounce
void loop() {
  gtlen = digitalRead(len);
  gtxuong = digitalRead(xuong);
  gtmenu = digitalRead(menu);
  gtback = digitalRead(back);

  unsigned long currentMillis = millis();
  if (currentMillis - lastDebounceTime > debounceDelay) {
    if (gtlen == LOW) {
      xuLyNutLen();
      lastDebounceTime = currentMillis;
    }
    if (gtxuong == LOW) {
      xuLyNutXuong();
      lastDebounceTime = currentMillis;
    }
    if (gtmenu == LOW) {
      xuLyNutMenu();
      lastDebounceTime = currentMillis;
    }
    if (gtback == LOW) {
      xuLyNutBack();
      lastDebounceTime = currentMillis;
    }
  }
}

void xuLyNutLen() {
  if (demtong == 1) { // Lên ở menu tổng
    congtru_tong = (congtru_tong >= 2) ? 0 : (congtru_tong + 1);
    menu_tong();
  } else if (demtong == 2) {
    if (congtru_tong == 0) {
      congtru_menu1 = (congtru_menu1 >= 1) ? 0 : 1;
      menu_1();
    } else if (congtru_tong == 1) {
      congtru_menu2 = (congtru_menu2 >= 1) ? 0 : 1;
      menu_2();
    } else if (congtru_tong == 2) {
      congtru_mode = (congtru_mode >= 1) ? 0 : 1;
      menu_chedo();
    }
  } else if (demtong == 3) {
    if (demmenu1 == 1) { // Điều chỉnh menu 1
      if (setmenu1 == 0 && gtnhietdov1 < 100) gtnhietdov1++;
      else if (setmenu1 == 1 && gtdoamv1 < 100) gtdoamv1++;
      caidat_menu1();
    } else if (demmenu2 == 1) { // Điều chỉnh menu 2
      if (setmenu2 == 0 && gtnhietdov2 < 100) gtnhietdov2++;
      else if (setmenu2 == 1 && gtdoamv2 < 100) gtdoamv2++;
      caidat_menu2();
    }
  }
}

void xuLyNutXuong() {
  if (demtong == 1) { // Xuống ở menu tổng
    congtru_tong = (congtru_tong <= 0) ? 2 : (congtru_tong - 1);
    menu_tong();
  } else if (demtong == 2) {
    if (congtru_tong == 0) {
      congtru_menu1 = (congtru_menu1 <= 0) ? 1 : 0;
      menu_1();
    } else if (congtru_tong == 1) {
      congtru_menu2 = (congtru_menu2 <= 0) ? 1 : 0;
      menu_2();
    } else if (congtru_tong == 2) {
      congtru_mode = (congtru_mode <= 0) ? 1 : 0;
      menu_chedo();
    }
  } else if (demtong == 3) {
    if (demmenu1 == 1) { // Điều chỉnh menu 1
      if (setmenu1 == 0 && gtnhietdov1 > 0) gtnhietdov1--;
      else if (setmenu1 == 1 && gtdoamv1 > 0) gtdoamv1--;
      caidat_menu1();
    } else if (demmenu2 == 1) { // Điều chỉnh menu 2
      if (setmenu2 == 0 && gtnhietdov2 > 0) gtnhietdov2--;
      else if (setmenu2 == 1 && gtdoamv2 > 0) gtdoamv2--;
      caidat_menu2();
    }
  }
}

void xuLyNutMenu() {
  if (demtong == 3 && demmenu1 == 1) {
    setmenu1 = (setmenu1 == 0) ? 1 : 0;
    caidat_menu1();
  } else if (demtong == 3 && demmenu2 == 1) {
    setmenu2 = (setmenu2 == 0) ? 1 : 0;
    caidat_menu2();
  } else {
    demtong++;
    if (demtong == 1) menu_tong();
    else if (demtong == 2) {
      if (congtru_tong == 0) menu_1();
      else if (congtru_tong == 1) menu_2();
      else if (congtru_tong == 2) menu_chedo();
    } else if (demtong == 3) {
      if (congtru_tong == 0) chonmenu_1();
      else if (congtru_tong == 1) chonmenu_2();
      else if (congtru_tong == 2) chon_chedo();
    }
  }
}

void xuLyNutBack() {
  if (demtong > 0) demtong--;
  if (demtong == 0) manhinh();
  else if (demtong == 1) menu_tong();
  else if (demtong == 2) {
    if (congtru_tong == 0) menu_1();
    else if (congtru_tong == 1) menu_2();
    else if (congtru_tong == 2) menu_chedo();
  }
}
