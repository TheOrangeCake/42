Inception project

#start a fresh vm:
- Vm mount share folder: mount -t vboxsf [-o OPTIONS] sharename mountpoint
- Install docker: docs.docker.com/engine/install/Ubuntu/
- Check if Docker running: `sudo systemctl status docker` if not `sudo systemctl start docker`

sudo echo "127.0.0.1   hoannguy.42.fr" >> /etc/hosts