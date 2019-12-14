set enc=utf-8
set fenc=utf-8
set termencoding=utf-8
set nocompatible
set autoindent
set smartindent
set tabstop=4        " tab width is 4 spaces
set shiftwidth=4     " indent also with 4 spaces
set expandtab        " expand tabs to spaces
set textwidth=120
set t_Co=256
syntax on
set showmatch
set comments=sl:/*,mb:\ *,elx:\ */
set backspace=indent,eol,start
set scrolloff=10
set ruler
let &colorcolumn=join(range(81,999),",")
highlight ColorColumn ctermbg=235 guibg=#2c2d27
autocmd BufWritePre * %s/\s\+$//e
