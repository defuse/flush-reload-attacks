require 'colorize'

class Print

  def self.error( msg )
    puts "[!] #{self.time} #{msg}".red
  end

  def self.warn( msg )
    puts "[?] #{self.time} #{msg}".yellow
  end

  def self.status( msg )
    puts "[+] #{self.time} #{msg}".green
  end

  def self.meta( msg )
    puts "[M] #{self.time} #{msg}".blue
  end

  def self.time
    duration = (Time.now() - $stats_start_time).to_i
    minutes = duration / 60
    seconds = duration % 60
    "%02d:%02d" % [minutes, seconds]
  end

end
