class Person
  def friend=(friend)
	@friend=friend
  end
end

a=2
b=a
p=Person.new
p.friend=Person.new
c=p
p=nil
