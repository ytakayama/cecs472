alias omni omniidl -bcxx -Wba -Wbtp
alias gxx "g++ -O2 -D__OMNIORB4__ -D_REENTRANT -D__x86__ -D __linux__  -D_OSVERSION__=2 -I/usr/local/include \!* -L/usr/local/omni/lib/ -lomniORB4 -lomnithread -lpthread "
alias go gxx train_colocate.cc
setenv LD_LIBRARY_PATH /usr/local/lib/
