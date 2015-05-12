require 'digest'

class Cache

  CACHE_DIRECTORY = 'cache'

  def self.set( key, value )
    return if $options[:nocache]
    self.make_cache_dir

    File.open( File.join( CACHE_DIRECTORY, self.sha256( key ) ), "w" ) do |f|
      f.print Marshal.dump( value )
    end

    return value
  end

  def self.get( key )
    return if $options[:nocache]
    self.make_cache_dir

    value = nil
    path = File.join( CACHE_DIRECTORY, self.sha256( key ) )
    if File.exists? path
      File.open( File.join( CACHE_DIRECTORY, self.sha256( key ) ), "r" ) do |f|
        value = Marshal.load( f.read )
      end
    end

    return value
  end

  def self.sha256( string )
    Digest::SHA256.new.hexdigest( string )
  end

  def self.sha256_file( path )
    File.open( path, "r" ) do |f|
      Digest::SHA256.new.hexdigest( f.read )
    end
  end

  def self.make_cache_dir
    unless Dir.exists? CACHE_DIRECTORY
      Dir.mkdir( CACHE_DIRECTORY )
    end
  end

end
