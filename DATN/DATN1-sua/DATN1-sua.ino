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
  } else if (congtru_mode == 1) {
    lcd.print("Che do: THU CONG");
    chedo = 1;
  }
  delay(2000); 
  menu_tong(); 
  demtong = 1; 
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

void loop() 
{
  gtlen = digitalRead(len);  
  gtxuong = digitalRead(xuong);  
  gtmenu = digitalRead(menu);
  gtback = digitalRead(back);

  // Xử lý nút Lên
  if (gtlen != macdinh)  // NÚT LÊN
  {
    if (gtlen == 0) // Khi nhấn nút lên
    {
      if (demtong == 1)   // LÊN Ở MENU TỔNG  
      {
        congtru_tong = (congtru_tong >= 2) ? 0 : (congtru_tong + 1);
        menu_tong();
      }
      
      else if (demtong == 2 && congtru_tong == 0)   // LÊN Ở MENU 1
      {
        congtru_menu1 = (congtru_menu1 >= 2) ? 0 : 1;  
        menu_1();
      }
      
      else if (demtong == 2 && congtru_tong == 1)   // LÊN Ở MENU 2
      {
        congtru_menu2 = (congtru_menu2 >= 2) ? 0 : 1;  
        menu_2();
      }
      else if (demtong == 2 && congtru_tong == 2)   // LÊN Ở menu_chedo
      {
        congtru_mode = (congtru_mode >= 2) ? 0 : 1;  
        menu_chedo();
      }
      else if (demtong == 3 && demmenu1 == 1) { // Chỉnh giá trị trong cài đặt V1
        if (setmenu1 == 0) { // Tăng nhiệt độ
          if (gtnhietdov1 < 100) {
            gtnhietdov1++;
          }
        } else if (setmenu1 == 1) { // Tăng độ ẩm
          if (gtdoamv1 < 100) {
            gtdoamv1++;
          }
        }
        caidat_menu1(); // Cập nhật màn hình hiển thị
        delay(200);
      }

      else if (demtong == 3 && demmenu2 == 1) { // Chỉnh giá trị trong cài đặt V2
        if (setmenu2 == 0) { // Tăng nhiệt độ V2
          if (gtnhietdov2 < 100) { 
            gtnhietdov2++;  
          }
        } else if (setmenu2 == 1) { // Tăng độ ẩm V2
          if (gtdoamv2 < 100) { 
            gtdoamv2++;  
          }
        }
        caidat_menu2();
        delay(200);
      }

      delay(200);
    }
    macdinh = gtlen;
  }

  // Xử lý nút Xuống
  if (gtxuong != macdinh) // NÚT XUỐNG
  {
    if (gtxuong == 0) // Khi nhấn nút xuống
    {
      if (demtong == 1)   // XUỐNG Ở MENU TỔNG
      {
        congtru_tong = (congtru_tong <= 0) ? 2 : (congtru_tong - 1);  
        menu_tong();
      }
      else if (demtong == 2 && congtru_tong == 0)   // XUỐNG Ở MENU 1
      {
        congtru_menu1 = (congtru_menu1 <= 0) ? 1 : 0;  
        menu_1();
      }
      
      else if (demtong == 2 && congtru_tong == 1)   // XUỐNG Ở MENU 2
      {
        congtru_menu2 = (congtru_menu2 <= 0) ? 1 : 0;  
        menu_2();
      }
      else if (demtong == 2 && congtru_tong == 2)   // XUỐNG Ở MENU_CHEDO
      {
        congtru_mode = (congtru_mode <= 0) ? 1 : 0;  
        menu_chedo();
      }

      else if (demtong == 3 && demmenu1 == 1) { // Chỉnh giá trị trong cài đặt V1
        if (setmenu1 == 0) { // Giảm nhiệt độ
          if (gtnhietdov1 > 0) {
            gtnhietdov1--;
          }
        } else if (setmenu1 == 1) { // Giảm độ ẩm
          if (gtdoamv1 > 0) {
            gtdoamv1--;
          }
        }
        caidat_menu1(); // Cập nhật màn hình hiển thị
        delay(200);
      }

      else if (demtong == 3 && demmenu2 == 1) { // Chỉnh giá trị trong cài đặt V2
        if (setmenu2 == 0) { // Giảm nhiệt độ V2
          if (gtnhietdov2 > 0) { 
            gtnhietdov2--;  
          }
        } else if (setmenu2 == 1) { // Giảm độ ẩm V2
          if (gtdoamv2 > 0) { 
            gtdoamv2--;  
          }
        }
        caidat_menu2();
        delay(200);
      }

      delay(200);
    }
    macdinh = gtxuong;
  }

  // Xử lý nút Menu
  if (gtmenu != macdinh)    // NÚT MENU
{  
  if (gtmenu == 0) // Khi nhấn nút
  {  
    if (demtong == 3 && demmenu1 == 1) { // Nếu đang ở menu V1
      if (setmenu1 == 0) {  // Nếu đang ở chế độ thông tin (chưa vào cài đặt)
        // Chuyển sang chế độ cài đặt
        setmenu1 = 1;
        caidat_menu1(); // Hiển thị chế độ cài đặt
      }
      else { // Nếu đang ở chế độ cài đặt, chuyển lại sang chế độ thông tin
        setmenu1 = 0;
        chonmenu_1(); // Hiển thị thông tin
      }
      delay(200);
    } 
    else if (demtong == 3 && demmenu2 == 1) { // Nếu đang ở menu V2
      if (setmenu2 == 0) {  // Nếu đang ở chế độ thông tin (chưa vào cài đặt)
        // Chuyển sang chế độ cài đặt
        setmenu2 = 1;
        caidat_menu2(); // Hiển thị chế độ cài đặt
      }
      else { // Nếu đang ở chế độ cài đặt, chuyển lại sang chế độ thông tin
        setmenu2 = 0;
        chonmenu_2(); // Hiển thị thông tin
      }
      delay(200);
    }
    else { // Không ở chế độ cài đặt, xử lý menu như bình thường
      demtong++;
      if (demtong == 1) // Ở menu tổng
      { 
        demback = 0;
        menu_tong(); 
      }
      else if (demtong == 2 && congtru_tong == 0) // Ở menu 1
      {
        demback = 0;
        menu_1(); 
        demmenu1++;
      }
      else if (demtong == 3 && demmenu1 == 1) // Chọn menu_1
      {
        demback = 0;
        chonmenu_1();  // Hiển thị thông tin V1
        delay(200);
      }  
      else if (demtong == 2 && congtru_tong == 1) // Ở menu 2
      {
        demback = 0;
        menu_2(); 
        demmenu2++;
      }
      else if (demtong == 3 && demmenu2 == 1) // Chọn menu_2
      {
        demback = 0;
        chonmenu_2();
        delay(200);
      }
      else if (demtong == 2 && congtru_tong == 2) // Chọn chế độ
      {
        demback = 0; // Chuyển vào chế độ chọn chi tiết
        menu_chedo();
        chedo++;
        
      }
      else if (demtong == 3 && congtru_tong == 2) // Chọn chế độ trong menu chi tiết
      {
        demback = 0;
        chon_chedo();
        delay(200);
      }


      else if (demtong > 4)
      {
        demtong = 4;
        demback = 0;
      }
    }
    delay(100);
  }
  macdinh = gtmenu;
}


  // Xử lý nút Back
 // Xử lý nút Back
if (gtback != macdinh)    // NÚT BACK
{  
    if (gtback == 0) // Khi nhấn nút
    {
        demback++;
        if (demback == 1)
        {
            if (demtong == 1 && congtru_tong == 2) // TỪ "CHE DO" VỀ "MÀN HÌNH CHÍNH"
            {
                demtong = 0;
                demback = 0;
                manhinh(); // Hiển thị màn hình chính
            }
            else if (demtong == 1 && (congtru_tong == 0 || congtru_tong == 1)) // TỪ MENU TỔNG VỀ MÀN HÌNH
            {
                demtong = 0;
                demback = 0;
                manhinh(); // Hiển thị màn hình chính
            }
            else if (demtong == 2 && congtru_tong == 0) // TỪ MENU 1 VỀ MENU TỔNG
            {
                demtong = 1;
                demback = 0;
                demmenu1 = 0;
                menu_tong();
            }
            else if (demtong == 2 && congtru_tong == 1) // TỪ MENU 2 VỀ MENU TỔNG
            {
                demtong = 1;
                congtru_tong = congtru_tong - 1;
                congtru_menu2 = 0;
                demmenu2 = 0;
                demback = 0;
                menu_tong();
            }
            else if (demtong == 2 && congtru_tong == 2) // TỪ MENU CHE DO VỀ MENU TỔNG
            {
                demtong = 1;
                congtru_tong = 0; // Reset trạng thái
                menu_tong();
            }
            else if (demtong == 3 && congtru_tong == 2) // BACK từ menu chế độ về menu tổng
            {
                demtong = 1;
                congtru_tong = 0; // Reset trạng thái
                menu_tong();
            }
            else if (demtong == 3 && demmenu1 >= 1) // TỪ CHỌN-MENU 1 VỀ MENU 1
            {
                demback = 0;
                demtong = 2;
                congtru_menu1 = 0;
                menu_1();
            } 
            else if (demtong == 3 && demmenu2 >= 1) // TỪ CHỌN-MENU 2 VỀ MENU 2
            {
                demback = 0;
                demtong = 2;
                congtru_menu2 = 0;
                menu_2();
            }  
            else if (demtong == 3 && chedo >= 1) // Từ chọn chế độ về chế độ
            {
                demback = 0;
                demtong = 2;
                congtru_mode = 0;
            }
            else if (demtong == 3 && demmenu1 >= 1 && (setmenu1 == 0 || setmenu1 == 1))
            {
                demback = 0;
                demtong = 2;
                setmenu1 = 0;
                congtru_menu1 = 0;
                menu_1();
            }
            else if (demtong == 3 && demmenu2 >= 1 && (setmenu2 == 0 || setmenu2 == 1))
            {
                demback = 0;
                demtong = 2;
                congtru_menu2 = 0;
                menu_2();
            }
            else if (demtong == 3 && chedo >= 1)
            {
                demback = 0;
                demtong = 2;
                congtru_mode = 0;
                menu_chedo();
            }
        }
        else
        {
            demback = 0;
        }
        delay(100);
    }
    macdinh = gtback;
}

}
