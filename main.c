#include <msp430.h> 

void Init(void);
int Data[5]={2,3,4,5,6};
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	unsigned int i;
    Init();
    while(1){
        for(i=0;i<5;i++) {
            UCA0TXBUF = Data[i];
            while (!(UCA0IFG & UCTXIFG));    // 判断是否发送完毕
        }
    }
}

void Init(void)
{
	UCA0CTL1 = UCSWRST;    //置位UCSWRST,使USCI复位，在其为1时初始化所有USCI寄存器
	UCA0CTL0 &= ~UC7BIT;       //设置数据长度为8位
	UCA0BR0 = 0x03;         //设置波特率为9600
	UCA0BR1 = 0x00;
	UCA0MCTL= 0x06;
	
	UCA0CTL1 |= UCSSEL__ACLK;  //选择辅助时钟32KHz
	P3SEL |= BIT3;             //P3.3为UCA0TXD
	P3DIR |= BIT3;

	UCA0CTL1 &= ~UCSWRST;   //软件清除UCSWRST
	UCA1IE |= UCRXIE;       // 使能接收中断
	_BIS_SR(GIE);           //开可屏蔽中断
}
