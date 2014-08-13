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
            while (!(UCA0IFG & UCTXIFG));    // �ж��Ƿ������
        }
    }
}

void Init(void)
{
	UCA0CTL1 = UCSWRST;    //��λUCSWRST,ʹUSCI��λ������Ϊ1ʱ��ʼ������USCI�Ĵ���
	UCA0CTL0 &= ~UC7BIT;       //�������ݳ���Ϊ8λ
	UCA0BR0 = 0x03;         //���ò�����Ϊ9600
	UCA0BR1 = 0x00;
	UCA0MCTL= 0x06;
	
	UCA0CTL1 |= UCSSEL__ACLK;  //ѡ����ʱ��32KHz
	P3SEL |= BIT3;             //P3.3ΪUCA0TXD
	P3DIR |= BIT3;

	UCA0CTL1 &= ~UCSWRST;   //������UCSWRST
	UCA1IE |= UCRXIE;       // ʹ�ܽ����ж�
	_BIS_SR(GIE);           //���������ж�
}
