class Fixnum
  def <=(other)
    self == other || self < other
  end

  def >=(other)
    self == other || self > other
  end
  
  alias :<=> :-
  
  def !=(other)
    !(self == other)
  end
  
  def succ
    self + 1
  end
  
  def inspect
    self.to_s
  end
end