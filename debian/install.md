# Install

Debian 11 "bullseye"

Смотрим список оборудования
```
lspci -nn | grep VGA
lspci -knn | grep "Net" -A2

```

Добавляем в файл sources.list источники для не свободного ПО
```
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
