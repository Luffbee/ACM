map <f9>:w<cr>:!g++ -std=c++11 -O2 -Wall % -o %< <cr>
map <f5>:w<cr>:!g++ -std=c++11 -O2 -Wall % -o %< && ./%< <cr>
map <f6>:w<cr>:!g++ -std=c++11 -g -Wall % -o %< && gdb %< <cr>
set ts=2 sts=2 ls=2 sw=2 et ai si nu hls mouse=
colorscheme elflord
