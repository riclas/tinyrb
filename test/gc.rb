class Person
  def friend=(friend)
	@friend=friend
  end
end

a=2
p=Person.new
p.friend=Person.new
p=nil
