#https://wiki.debian.org/ru/Make-Kpkg
#Из сети *.deb пакеты скачиваются в папку ls /var/cache/apt/archives/
 sudo su -
 uname -r
#Подключаем второй жёсткий диск. http://did5.ru/it/kak-podklyuchit-dopolnitelnyj-zhestkij-disk-v-ubuntu.html
 fdisk -l
 fdisk /dev/sdb
 n
 p
 <Enter>
 w
 mkfs.ext4 /dev/sdb1
 mkdir /media/d2/
 mount /dev/sdb1 /media/d2/
 vim /etc/fstab
 /dev/sdb1 /media/d2/ ext4 defaults 1 2

#Установка необходимых пакетов.
 apt-get update
 apt-get install kernel-package libncurses5-dev fakeroot wget bzip2 build-essential
 cd /usr/src/
 wget https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.7.2.tar.xz
 tar -C /usr/src/ -xpJf linux-4.7.2.tar.xz

#Удаляем символьную ссылку предыдущего ядра.
 rm /usr/src/linux
 ln -s /usr/src/linux-4.7.2/ /usr/src/linux
 cd /usr/src/linux/
#Можно установить патчи (заплатки ядра)
#...

#Использование существующего конфигурационного файла работающего ядра и для нового.
 make clean && make mrproper
 cp /boot/config-`uname -r` ./.config
 make menuconfig

#Выполняем конфигурирование ядра, бираем в меню конфигуратора пункт "Load an Alternate
#Configuration File" или "Load" и нажимаем "Оk",
#загрузится файл .config.
#Затем (если требуется) сделайте необходимые изменения в конфигурации ядра перемещаясь по меню.
#Для завершения нажать "Exit",
#будет задан вопрос "Do you wish to save your new kernel configuration?", отвечаем утвердительно "Yes". 

#Сборка (компиляция) ядра (потребуется 12 ГБ места на жёстком диске).
 make-kpkg clean
 fakeroot make-kpkg --initrd --append-to-version=-linux-4.7.2my kernel_image kernel_headers
#Опция --append-to-version= задаёт название файла ядра.
#Процесс компиляции и сборки .deb пакетов может занят довольно продолжительное время.
 
 
#Когда удачно завершится сборка ядра, в каталоге /usr/src будут созданы два .deb пакета: 
 ls -l /usr/src/
 linux-image-4.7.2-linux-4.7.2my_4.7.2-linux-4.7.2my-10.00.Custom_amd64.deb
 linux-headers-4.7.2-linux-4.7.2my_4.7.2-linux-4.7.2my-10.00.Custom_amd64.deb
#linux-image-*.deb - собственно само актуальное ядро и
#linux-headers-*.deb - заголовки ядра, необходимые для сборки других модулей (например при сборке модулей драйвера nVidia).
 
#Устанавливаем deb пакеты (эти пакеты теперь могут быть установлены на другой системе и собирать их заново уже не будет необходимости).
 dpkg -i linux-image-4.7.2-linux-4.7.2my_4.7.2-linux-4.7.2my-10.00.Custom_amd64.deb
 dpkg -i linux-headers-4.7.2-linux-4.7.2my_4.7.2-linux-4.7.2my-10.00.Custom_amd64.deb
 init 6
 uname- r
 4.7.2-linux-4.7.2my
 
 
#Если после перезагрузки, выбранное вами новое ядро не загружается, перезагрузитесь и выберите.
#Ваше предыдущее ядро и можно попробовать проделать весь процесс заново,
#чтоб собрать рабочее ядро.
#Не забывайте в таком случае удалить строчки нерабочего ядра в /boot/grub/menu.lst.

