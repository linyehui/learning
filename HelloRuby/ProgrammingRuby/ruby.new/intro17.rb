histogram = Hash.new(0)
p histogram['ruby']
histogram['ruby'] = histogram['ruby'] + 1
p histogram['ruby']


inst_section = {
	cello:		'string',
	clarinet:	'woodwind',
	drum:		'percussion',
	oboe:		'woodwind',
	trumpet:	'brass',
	violin:		'string'
}

puts "An oboe is a #{inst_section[:oboe]}"

radiation = 3001
if radiation > 3000
	puts "Danger, Will Robinson"
end

puts "Danger, Will Robinson" if radiation > 3000


square = 2
while square < 10
	puts square = square*square
end

square = 2
puts square = square*square while square < 10