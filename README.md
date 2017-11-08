# Linux

## Работа с архивом

|Команда|Описание|
|-------|--------|
|tar -xvf archive.tar.bz2 -C /tmp/folder1/|Распаковка архива tar.bz2 в папку /tmp/folder1/|
|tar -xvf archive.tar.gz |Распаковка архива tar.gz в текущую папку|
|tar -tf archive.tar.gz|Просмотр содержимого архива|


Установка дополнений к гостевой машине (Debian 9) от VirtualBox 5.1.30 

apt-get update
# apt-get upgrade
apt-get install build-essential module-assistant -y
m-a prepare -y
cd /media/cdrom0
sh ./VBoxLinuxAdditions.run
reboot
