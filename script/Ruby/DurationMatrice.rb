## Test création et remplissage matrice
class DurationMatrice
    def initialize()
        array = Array.new(1000) { Array.new(1000) { rand(10001) }}
        /puts array/
        out_file = File.open("out.txt", "w+")
        /$i = 0
        while $i < 1000000 do
            out_file.puts(rand(10001))
            $i+=1
        end/
        array2 = out_file.read
        /puts array2/
        out_file.close
    end
end

d = DurationMatrice.new
