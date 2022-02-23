# Install

Debian 11 "bullseye"

Смотрим список оборудования
```
lspci -nn | grep VGA
lspci -knn | grep "Net" -A2

```
Контроллер сетевой карты
```
Ralink RT3290LE 802
```

Добавляем в файл sources.list источники для не свободного ПО
```
su -
nano /etc/apt/sources.list
```
Содержимое файла:
```
deb http://deb.debian.org/debian/ bullseye main contrib non-free
deb-src http://deb.debian.org/debian/ bullseye main contrib non-free

deb http://security.debian.org/debian-security bullseye-security main contrib non-free
deb-src http://security.debian.org/debian-security bullseye-security main contrib non-free

deb http://ftp.de.debian.org/debian/ bullseye main contrib non-free
```
Обновляем пакеты дистрибутива
```
sudo apt-get update
sudo apt-get upgrade
sudo apt autoremove
```
Устанавливаем пакет микропрограмм для сети и видиокарты
```
apt-get install firmware-misc-nonfree
```
Описание  
[wiki.debian.org](https://wiki.debian.org/rt2800usb)
