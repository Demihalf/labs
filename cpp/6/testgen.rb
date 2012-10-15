#!/usr/bin/env ruby
# encoding: UTF-8

if ARGV.size < 2 then
    puts "Usage: testgen.rb COUNT OUT_FILE"
    exit 1
end

n = ARGV[0].to_i

names = File.readlines("names.txt")

File.open(ARGV[1], "w") do |f|
    f.puts n

    f.puts

    rnd = Random.new

    n.times do
        f.puts names.sample
        f.puts rnd.rand(1..7)

        3.times do 
            f.puts rnd.rand(2..5)
        end

        f.puts
    end
end
