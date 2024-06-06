" Title:        FlexibleVP 
" Description:  Vim plugin that enables launching applications and webpages from within Vim
" Last Change:  8 July 2023
" Maintainer:   SuprimeBG <https://github.com/SuprimeBG/flexibleVP>

if exists('g:loaded_flexibleVP')
  finish
endif
let g:loaded_flexibleVP = 1


command! -nargs=1 Launch call Launch(<q-args>)
command! -nargs=+ Addw call Addwebaddress(<f-args>)
command! -nargs=+ Adda call Addapp(<f-args>)
command! -nargs=0 Listw call ListWebAddresses()
command! -nargs=0 Lista call ListAppAddresses()
