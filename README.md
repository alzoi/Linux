# Linux

## Просмотр кода ядра
https://elixir.bootlin.com/linux/latest/source

## Документация ядра
https://refspecs.linuxbase.org/lsb.shtml  
https://refspecs.linuxbase.org/LSB_3.1.1/LSB-Core-generic/LSB-Core-generic/libc.html  

## Работа с архивом

|Команда|Описание|
|-------|--------|
|tar -xvf archive.tar.bz2 -C /tmp/folder1/|Распаковка архива tar.bz2 в папку /tmp/folder1/|
|tar -xvf archive.tar.gz |Распаковка архива tar.gz в текущую папку|
|tar -tf archive.tar.gz|Просмотр содержимого архива|


Установка дополнений к гостевой машине (Debian 9) от VirtualBox 5.1.30

    sudo su -
    apt-get update
    apt-get upgrade # Можно не выполнять.
    apt-get install build-essential module-assistant -y
    m-a prepare -y
    cd /media/cdrom0
    sh ./VBoxLinuxAdditions.run
    reboot

Чтобы получить доступ к общей папке хост машины необходимо пользователя добавить в группу vboxsf

    usermod -a -G vboxsf user
    
Узнать версию дистрибутива Debian

    lsb_release -a

Работа с виртуальной и физической памятью процесса  
http://qaru.site/questions/218681/procpidpagemaps-and-procpidmaps-linux

Высоконагруженные системы  
https://habrahabr.ru/company/odnoklassniki/blog/347798/

В конфигурационных файлах некоторые запрещённые символы необходимо экранировать
https://en.wikipedia.org/wiki/Percent-encoding#Percent-encoding_reserved_characters  
пример настроки proxy сервера
```
export http_proxy="http://dom%5Cuser:pass@proxy:port"
# символ \ экранирован %5C
export http_proxy="http://dom\user:pass@proxy.ru:3128"
```

# Работа с оперативной памятью
https://habr.com/ru/post/487898/

# WSL
[docs.microsoft.com/ru-ru/windows/wsl](https://docs.microsoft.com/ru-ru/windows/wsl/basic-commands#set-wsl-version-to-1-or-2)
```
wsl --list --online
wsl --install --distribution Debian
wsl --distribution <Distribution Name> --user <User Name>
```

# Установка Debian
https://www.debian.org/releases/stable/amd64/  
https://cdimage.debian.org/cdimage/unofficial/non-free/cd-including-firmware/current/  
https://cdimage.debian.org/cdimage/unofficial/non-free/cd-including-firmware/11.2.0+nonfree/  
http://ftp.ru.debian.org/debian/pool/non-free/f/firmware-nonfree/  

Файл ресурсов (https://wiki.debian.org/ru/SourcesList)
```
sudo nano /etc/apt/sources.list
```

```
sudo dpkg -i firmware-realtek_20210315-3_all.deb
```
# grub
```
sudo nano /etc/default/grub
GRUB_DEFAULT=0 заменить на 2 (будет загружаться треться запись в grub)
GRUB_TIMEOUT=10 заменить на 3
sudo update-grub
```

# Ошибки
[Устранение проблем с разрешением экрана (графика)](https://unix.stackexchange.com/questions/657983/troubleshoot-problems-with-screen-resolution-graphics-in-gnu-linux-installers/657984#657984)
