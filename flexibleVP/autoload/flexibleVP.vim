command! -nargs=1 Launch call Launch(<q-args>)
command! -nargs=+ Addw call Addwebaddress(<f-args>)
command! -nargs=+ Adda call Addapp(<f-args>)
command! -nargs=0 Listw call ListWebAddresses()
command! -nargs=0 Lista call ListAppAddresses()

function! Launch(app)

  let web_addresses_file = expand('~/vimfiles/plugged/flexibleVP/data/webaddress.txt')
  let app_addresses_file = expand('~/vimfiles/plugged/flexibleVP/data/appaddress.txt')

  let web_addresses = readfile(web_addresses_file)
  let app_addresses = readfile(app_addresses_file)

  let address = ''
  let is_web_address = 0

  for line in web_addresses
    if line =~ '^' . a:app . ':'
      let address = substitute(line, '^' . a:app . ':\s*', '', '')
      let is_web_address = 1
      break
    endif
  endfor

  if empty(address)
    for line in app_addresses
      if line =~ '^' . a:app . ':'
        let address = substitute(line, '^' . a:app . ':\s*', '', '')
        break
      endif
    endfor
  endif

  if empty(address)
    echo 'Address for ' . a:app . ' not found.'
  else
    if is_web_address
      if has('win32') || has('win64')
        let cmd = 'start "" ' . shellescape(address, 1)
        call system(cmd)
      elseif has('macunix')
        let cmd = 'open ' . shellescape(address, 1)
        call system(cmd)
      else
        let cmd = 'xdg-open ' . shellescape(address, 1)
        call system(cmd)
      endif
    else
      if has('win32') || has('win64')
        let cmd = 'start "" ' . shellescape(address, 1)
        call system(cmd)
      else
        let cmd = 'xdg-open ' . shellescape(address, 1)
        call system(cmd)
      endif
    endif
  endif

endfunction

function! Addwebaddress(name, address)

  let web_addresses_file = expand('~/vimfiles/plugged/flexibleVP/data/webaddress.txt')
  let web_addresses = readfile(web_addresses_file)

  if stridx(a:address, 'http://') == 0 || stridx(a:address, 'https://') == 0
    let new_address = a:address
  else
    if stridx(a:address, 'www.') != 0
      let new_address = 'https://www.' . a:address
    else
      let new_address = 'https://' . a:address
    endif
  endif

  let existing_modified_address = a:name . ': ' . new_address
  let matching_modified_address = filter(web_addresses, 'v:val =~# "^" . existing_modified_address . ":"')
  if !empty(matching_modified_address)
    echo 'Web address already exists: ' . matching_modified_address[0]
    return
  endif

  let new_line = a:name . ': ' . new_address

  if !index(web_addresses, new_line)
    call writefile(web_addresses + [new_line], web_addresses_file)
    echo 'Web address added: ' . new_line
  else
    echo 'Web address address already exists: ' . new_line
  endif

endfunction

function! Addapp(name, address)

  let app_addresses_file = expand('~/vimfiles/plugged/flexibleVP/data/appaddress.txt')
  let app_addresses = readfile(app_addresses_file)
  let new_line = a:name . ': ' . a:address

  if index(app_addresses, new_line) != -1
    echo 'App address already exists: ' . new_line
    return
  endif

  let matching_name = filter(app_addresses, 'v:val =~# "^" . a:name . ":"')
  if !empty(matching_name)
    echo 'App with the same name already exists: ' . matching_name[0]
    return
  endif

  call writefile(app_addresses + [new_line], app_addresses_file)
  echo 'App address added: ' . new_line

endfunction

function! ListWebAddresses()

  let web_addresses_file = expand('~/vimfiles/plugged/flexibleVP/data/webaddress.txt')
  let web_addresses = readfile(web_addresses_file)

  if empty(web_addresses)
    echo "No web addresses found."
    return
  endif

  if has("gui_running") || &termguicolors
    tabnew
    setlocal buftype=nofile bufhidden=wipe
  else
    new
  endif

  setlocal nowrap
  setlocal modifiable
  put =web_addresses
  normal gg

endfunction

function! ListAppAddresses()

  let app_addresses_file = expand('~/vimfiles/plugged/flexibleVP/data/appaddress.txt')
  let app_addresses = readfile(app_addresses_file)

  if empty(app_addresses)
    echo "No app addresses found."
    return
  endif

  if has("gui_running") || &termguicolors
    tabnew
    setlocal buftype=nofile bufhidden=wipe
  else
    new
  endif

  setlocal nowrap
  setlocal modifiable
  put =app_addresses
  normal gg

endfunction
