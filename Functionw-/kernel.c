void outb(unsigned short p, unsigned char d) { __asm__("out %%al, %%dx" : : "a" (d), "d" (p)); }
void outw(unsigned short p, unsigned short d) { __asm__("out %%ax, %%dx" : : "a" (d), "d" (p)); }
unsigned char inb(unsigned short p) { unsigned char r; __asm__("in %%dx, %%al" : "=a" (r) : "d" (p)); return r; }

#define VBE_MEM 0xFD000000

void draw_px(int x, int y, unsigned short c) {
    unsigned short* v = (unsigned short*)VBE_MEM;
    if(x>=0 && x<800 && y>=0 && y<600) v[y*800+x] = c;
}

void draw_box(int x, int y, int w, int h, unsigned short c) {
    for(int i=0; i<w; i++) for(int j=0; j<h; j++) draw_px(x+i, y+j, c);
}

int m_x = 400, m_y = 300, win_x = 150, win_y = 150, drag = 0;
unsigned short bg = 0x39C7;

void render() {
    draw_box(0, 0, 800, 600, bg);
    draw_box(0, 570, 800, 30, 0x7BEF);
    draw_box(5, 575, 60, 20, 0xF800);
    draw_box(win_x, win_y, 240, 180, 0xC618);
    draw_box(win_x, win_y, 240, 18, 0x001F);
}

void m_wait(int t) {
    int timeout = 100000;
    if(t==0) while(timeout--) if(inb(0x64)&1) return;
    else while(timeout--) if(!(inb(0x64)&2)) return;
}

void m_init() {
    m_wait(1); outb(0x64, 0xA8);
    m_wait(1); outb(0x64, 0x20);
    m_wait(0); unsigned char s = (inb(0x60)|2);
    m_wait(1); outb(0x64, 0x60); m_wait(1); outb(0x60, s);
    m_wait(1); outb(0x64, 0xD4); m_wait(1); outb(0x60, 0xF4); inb(0x60);
}

void main() {
    m_init();
    render();
    while(1) {
        if(inb(0x64) & 0x21) {
            unsigned char st = inb(0x64);
            if(st & 0x20) {
                unsigned char b = inb(0x60);
                char dx = (char)inb(0x60); char dy = (char)inb(0x60);
                draw_box(m_x, m_y, 5, 5, bg);
                m_x += dx; m_y -= dy;
                if(m_x<0) m_x=0; if(m_x>795) m_x=795;
                if(m_y<0) m_y=0; if(m_y>595) m_y=595;
                if((b&1) && m_x > win_x && m_x < win_x+240 && m_y > win_y && m_y < win_y+18) drag = 1;
                if(!(b&1)) drag = 0;
                if(drag) { win_x += dx; win_y -= dy; render(); }
                draw_box(m_x, m_y, 5, 5, 0xFFFF);
            }
            unsigned char sc = inb(0x60);
            if(sc == 0x13) outb(0x64, 0xFE);
            if(sc == 0x1F) outw(0x604, 0x2000);
        }
    }
}
