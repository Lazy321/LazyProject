# LazyProject
My first OS project called LazyOS. Built from scratch in C/Asm. I'm a beginner, so don't be too harsh!
👋 Welcome to my first OS project! / Добро пожаловать!

EN:
Hi there! and this is my very first project in OS development — LazyOS. 
To be honest, I'm still learning and I'm not a pro programmer yet, so the code might look messy or noob-ish. 
Please don't judge too strictly! I'm just a guy trying to understand how computers work at the lowest level. 
Feel free to explore my work and give some advice!

RU:
Всем привет! и это моя самая первая работа по разработке операционной системы — LazyOS.
Честно говоря, я только учусь и пока не очень хорош в программировании, поэтому код может выглядеть коряво или по-детски. 
Пожалуйста, не судите строго! Я просто парень, который пытается понять, как работают компьютеры на самом низком уровне.
Заходите, смотрите мои наработки, буду рад советам!
 

  Плюсы / Pros
RU:
* Свой загрузчик: Полный контроль над переходом в 32-битный режим.
* Высокое разрешение: VESA 800x600 16-bit (65к цветов) — это красиво.
* Работа с железом: Прямое общение с портами мыши и клавиатуры.
* Скорость: Всё работает в Ring 0, никаких лишних слоев и задержек.

EN:
* Custom Bootloader: Full control over 16-to-32 bit transition.
* High Resolution: VESA 800x600 16-bit (65k colors) looks great.
* Direct Hardware Access: Communication with mouse/keyboard.
* Performance: Everything runs in Ring 0 with zero overhead.



#Минусы / Cons
RU:
* Нестабильность: Возможны вылеты и перезагрузки .
* Монолитность: Весь код в одном файле `kernel.c`, сложно расширять.
* Проблемы с мышью: Курсор иногда глючит у краев экрана.
* Нет ФС: Все данные пока жестко прописаны в коде.

EN:
* Instability: Potential crashes and reboots (Interrupts need debugging).
* Monolithic: All logic is in `kernel.c`, making it hard to scale.
* Mouse Issues: Cursor glitches near the screen borders.
* No Filesystem: All data is currently hardcoded in the kernel.
