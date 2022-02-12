# frozen_string_literal: true

Screen.init

x = 10
while true
  Screen.clear
  Screen.print 'Hello World', x, 10
  x += 2
  x = 10 if x >= 118

  sleep 100
end
