# frozen_string_literal: true

i = 0
while i < 100
  point = Point.new(i, 0)
  puts point.to_s
  sleep 10
  i += 1
end
