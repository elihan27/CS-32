

 class File
 
 {
 public:
     File (string name);
     virtual ~File();
     string name() const;
     virtual void open()const=0;
     virtual void redisplay()const;
     
 private:
     string m_name;
 
 };
 
 class TextMsg : public File
 {
 
 public:
     TextMsg (string name);
     virtual ~TextMsg();
     virtual void open() const;
     
 
 private:
     string m_name;

 };
 
 
 class Picture : public File
{
 public:
    Picture (string name);
    virtual ~Picture();
    virtual void open() const;
   

 private:
    string m_name;
};

 
 
 class Video : public File
 
 {
 public:
     Video (string name, int runtime);
     virtual ~Video();
     virtual void open() const;
     virtual void redisplay() const;
 
 private:
     string m_name;
     int m_runtime;
 
 };

///constructors


File :: File (string name): m_name(name)
{}

TextMsg :: TextMsg(string name) : File(name)
{}

Picture :: Picture(string name): File(name)
{}

Video:: Video(string name, int runtime): File(name), m_runtime(runtime)
{}

//deconstuctors

File::~File()
{
}

TextMsg::~TextMsg()
{
    cout << "Destroying " << name() << ", a text message"<< endl;
    

}
Picture::~Picture()
{
    cout << "Destroying the picture " << name() << endl;
    
}

Video::~Video()
{
     cout << "Destroying " << name() << ", a video"<< endl;
    
}






 
string File::name() const
 
 {
     return m_name;
 }

void File:: redisplay() const
{

    cout << "refresh the screen";
}


void Video:: redisplay() const
{
    
    cout << "replay the video";
}

void File:: open() const
{
}

void TextMsg ::open() const
{

    cout << "open text message";
}

void Video ::open() const
{
    
    cout << "play " << m_runtime << " second video";
    
}

void Picture ::open()const 
{
    
    cout << "show picture";
}


 
 
 
 
