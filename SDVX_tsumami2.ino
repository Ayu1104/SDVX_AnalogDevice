//つまみ片方
// ロータリーエンコーダーの配線に合わせる
int dRotAPin  = 2;
int dRotBPin  = 4;
int R_count   = 0;
// ロータリーエンコーダーの状態を記憶する
// 割り込み中に変化する変数はvolatileはをつけて宣言する
volatile int m_nOldRot = 0;
volatile int m_nValue  = 0;

int input_1 = 0;
int input_2 = 0;
char outchar;

void setup()
{
 
  // ピンの設定
  // INPUTモードにします。
  pinMode(dRotAPin, INPUT);
  pinMode(dRotBPin, INPUT);
 
  // プルアップを有効にします
  digitalWrite(dRotAPin, HIGH);
  digitalWrite(dRotBPin, HIGH);
 
  // 外部割り込みを設定します
  // D2ピンが 変化 した時にrotRotEnd()を呼び出します
  attachInterrupt(0, rotRotEnc, CHANGE);
  //シリアル通信速度を設定します
  Serial.begin(9600);
}
 
void loop()
{
  //シリアルモニターに角度を表示させる
  if(m_nValue == 10){
    R_count++;
    m_nValue = 0;
  }
  if(m_nValue == -10){
    R_count--;
    m_nValue = 0;
  }
  Serial.println(R_count);
  input_1 = R_count;
  delay(100);
  input_2 = R_count;
  
  //ここの条件文を変える
  if(input_2 > input_1){
    outchar='q';
  }else if(input_2 < input_1){
    outchar='w';
  }
}
 
// 外部割り込みから呼び出される変数
void rotRotEnc(void)
{
  if(!digitalRead(dRotAPin)){  // ロータリーエンコーダー回転開始
    if(digitalRead(dRotBPin)){
      //右回転
      m_nOldRot = 'R';
    } else {
      //左回転
      m_nOldRot = 'L';
    }
  } else {  // ロータリーエンコーダー回転停止
    if(digitalRead(dRotBPin)){
      if(m_nOldRot == 'L'){
        // 左回転の時の処理
        m_nValue--;
      }
    } else {
      if(m_nOldRot == 'R'){
        //右回転の時の処理
        m_nValue++;
      }
    }
    // ここでロータリーエンコーダーの状態をクリア
    m_nOldRot = 0;
  }
}

