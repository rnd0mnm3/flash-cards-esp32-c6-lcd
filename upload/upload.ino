int NumberOfWords = 143;

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <efontEnableCJK.h> // Requires 'efontWrapper' or 'efont' library

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7789    _panel_instance;
  lgfx::Bus_SPI         _bus_instance;
  lgfx::Light_PWM       _light_instance;

public:
  LGFX(void) {
    auto cfg = _bus_instance.config();
    cfg.spi_host = SPI2_HOST;
    cfg.spi_mode = 0;
    cfg.freq_write = 40000000;
    cfg.freq_read  = 16000000;
    cfg.spi_3wire  = true;
    cfg.use_lock   = true;
    cfg.dma_channel = SPI_DMA_CH_AUTO;
    cfg.pin_sclk = 1;   
    cfg.pin_mosi = 2;   
    cfg.pin_miso = -1;  
    cfg.pin_dc   = 15;  
    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);

    auto pcfg = _panel_instance.config();
    pcfg.pin_cs   = 14;   
    pcfg.pin_rst  = 22;   
    pcfg.pin_busy = -1;
    pcfg.panel_width  = 172;
    pcfg.panel_height = 320;
    pcfg.offset_x = 34;
    pcfg.offset_y = 0;
    pcfg.offset_rotation = 0;
    pcfg.dummy_read_pixel = 8;
    pcfg.dummy_read_bits  = 1;
    pcfg.readable = true;
    pcfg.invert = false; 
    pcfg.rgb_order = false;
    pcfg.dlen_16bit = false;
    pcfg.bus_shared = false;
    _panel_instance.config(pcfg);

    auto lcfg = _light_instance.config();
    lcfg.pin_bl = 23;     
    lcfg.invert = false;
    lcfg.freq   = 44100;
    lcfg.pwm_channel = 0;
    _light_instance.config(lcfg);
    _panel_instance.setLight(&_light_instance);

    setPanel(&_panel_instance);
  }
};

LGFX lcd;

char *TargetLang[] = {
    "你", "好", "请", "问", "贵", "姓", "我", "呢", "小姐", "叫", "什么", "名字", "先生", "是", "老师", "吗", "不", "学生", "也", "人", "中国", "北京", "美国", "纽约", "那", "的", "照片", "这", "爸爸", "妈妈", "个", "女", "孩子", "谁", "她", "姐姐", "男", "弟弟", "他", "大哥", "儿子", "有", "女儿", "没", "家", "几", "口", "哥哥", "两", "妹妹", "和", "大姐", "二姐", "做", "工作", "律师", "英文", "都", "大学生", "医生", "九月", "月", "十二", "号", "星期", "星期四", "天", "生日", "今年", "多", "大", "十八", "岁", "吃", "饭", "怎么样", "太…了", "谢谢", "喜欢", "菜", "还是", "可是", "我们", "点", "半", "晚上", "见", "再见", "现在", "刻", "事", "今天", "很", "忙", "明天", "晚饭", "为什么", "因为", "还", "同学", "认识", "朋友", "英国", "周末", "打球", "看", "电视", "唱歌", "跳舞", "听", "音乐", "书", "对", "有的", "时候", "电影", "常常", "那", "去", "外国", "请客", "昨天", "所以", "小", "好久", "不错", "想", "觉得", "有意思", "只", "睡觉", "算了", "找", "别人", "呀", "进", "快", "进来", "来", "介绍", "一下", "高兴", "漂亮", "坐", "在", "哪儿", "学校", "喝", "点", "茶", "咖啡", "吧", "要", "瓶", "可乐", "可以", "对不起", "给", "杯", "水", "玩", "了", "图书馆", "一起", "聊天", "才", "回家"
};

char *Phonetics[] = {
    "nǐ", "hǎo", "qǐng", "wèn", "guì", "xìng", "wǒ", "ne", "xiǎojiě", "jiào", "shénme", "míngzi", "xiānsheng", "shì", "lǎoshī", "ma", "bù", "xuésheng", "yě", "rén", "Zhōngguó", "Běijīng", "Měiguó", "Niǔyuē", "nà", "de", "zhàopiàn", "zhè", "bàba", "māma", "gè/ge", "nǚ", "háizi", "shéi", "tā", "jiějie", "nán", "dìdi", "tā", "dàgē", "érzi", "yǒu", "nǚ’ér", "méi", "jiā", "jǐ", "kǒu", "gēge", "liǎng", "mèimei", "hé", "dàjiě", "èrjiě", "zuò", "gōngzuò", "lǜshī", "Yīngwén", "dōu", "dàxuéshēng", "yīshēng", "jiǔyuè", "yuè", "shí’èr", "hào", "xīngqī", "xīngqīsì", "tiān", "shēngrì", "jīnnián", "duō", "dà", "shíbā", "suì", "chī", "fàn", "zěnmeyàng", "tài…le", "xièxie", "xǐhuan", "cài", "háishi", "kěshì", "wǒmen", "diǎn", "bàn", "wǎnshang", "jiàn", "zàijiàn", "xiànzài", "kè", "shì", "jīntiān", "hěn", "máng", "míngtiān", "wǎnfàn", "wèishénme", "yīnwèi", "hái", "tóngxué", "rènshi", "péngyou", "Yīngguó", "zhōumò", "dǎ qiú", "kàn", "diànshì", "chàng gēr", "tiào wŭ", "tīng", "yīnyuè", "shū", "duì", "yǒude", "shíhou", "diànyǐng", "chángcháng", "nà", "qù", "wàiguó", "qǐng kè", "zuótiān", "suǒyǐ", "xiǎo", "hǎo jiǔ", "búcuò", "xiǎng", "juéde", "yǒu yìsi", "zhǐ", "shuì jiào", "suàn le", "zhǎo", "biérén", "ya", "jìn", "kuài", "jìn lai", "lái", "jièshào", "yí xià", "gāoxìng", "piàoliang", "zuò", "zài", "nǎr", "xuéxiào", "hē", "diǎn", "chá", "kāfēi", "ba", "yào", "píng", "kělè", "kěyǐ", "duìbuqǐ", "gěi", "bēi", "shuǐ", "wán", "le", "túshūguǎn", "yìqǐ", "liáo tiān", "cái", "huí jiā"
};

char *Meaning[] = {
    "you", "fine, good, nice, OK", "please (polite), to treat or to invite sb", "to ask (a question)", "honorable, expensive", "(one’s) family name is . . . ; family name", "I, me", "(question particle)", "Miss, young lady", "to be called, to call", "what", "name", "Mr., husband, teacher", "to be", "teacher", "(question particle)", "not, no", "student", "too, also", "people, person", "China", "Beijing", "America", "New York", "that", "(a possessive or descriptive particle)", "picture, photo", "this", "father, dad", "mother, mom", "(measure word for many common everyday objects)", "female", "child", "who, whom", "she, her", "older sister", "male", "younger brother", "he, him", "eldest/oldest brother", "son", "to have, to exist", "daughter", "not", "family, home", "how many, some, a few", "(measure word for number of family members)", "older brother", "two, a couple of", "younger sister", "and", "eldest/oldest sister", "second oldest sister", "second oldest sister", "job; to work", "lawyer", "the English language", "both, all", "college student", "doctor, physician", "September", "month", "twelve", "(measure word for position in a numerical series, day of the month)", "week", "Thursday", "day", "birthday", "this year", "how many/much, to what extent", "big, old", "eighteen", "year (of age)", "to eat", "meal, (cooked) rice", "Is it OK? How is that? How does that sound?", "too, extremely", "to thank", "to like", "dish, cuisine", "or", "but", "we, us", "o’clock", "half, half an hour", "evening, night", "to see", "goodbye, see you again", "now", "quarter", "matter, affair, event", "today", "very", "busy", "tomorrow", "dinner, supper", "why", "because", "also, too, as well", "classmate", "to be acquainted with, to recognize", "friend", "Britain", "weekend", "to play ball", "to watch, to look, to read", "television", "to sing (a song)", "to dance", "to listen", "music", "book", "right, correct", "some", "(a point in) time, moment, (a duration of) time", "movie", "often", "in that case, then", "to go", "foreign country", "to invite someone (to dinner, coffee, etc.), to play the host", "yesterday", "so", "small, little", "a long time", "pretty good", "to want to, would like to", "to feel, to think", "interesting", "only", "to sleep", "forget it, never mind", "to look for", "other people, another person", "(interjectory particle used to soften a question)", "enter", "fast, quick; quickly", "to come in", "to come", "to introduce", "once, a bit", "happy, pleased", "pretty", "to sit", "at, in, on", "where", "school", "to drink", "a little, a bit, some", "tea", "coffee", "a sentence-final particle", "to want", "(measure word for bottled liquid, etc.)", "cola", "can, may", "sorry", "to give", "(measure word for things contained in a cup or glass)", "water", "to have fun, to play", "a dynamic particle", "library", "together", "to chat", "not until, only then", "to go home"
};

void setup(void) {
  lcd.init();
  lcd.setRotation(5);
  lcd.fillScreen(TFT_BLACK);
}

void loop(void) {
  int counter = random(NumberOfWords);

  lcd.fillScreen(TFT_BLACK);
  
  // Set Chinese Unicode Font (efont CN 16px)
  lcd.setFont(&fonts::efontCN_16);
  
  // Target Language text (Chinese)
  lcd.setCursor(10, 15);
  lcd.setTextColor(TFT_WHITE);
  lcd.setTextSize(2);
  lcd.print(TargetLang[counter]); 

  // Phonetics text (Pinyin)
  lcd.setCursor(10, 70);
  lcd.setTextColor(TFT_GREEN);
  lcd.setTextSize(2);
  lcd.print(Phonetics[counter]); 

  // Meaning text (English translation)
  lcd.setCursor(10, 110);
  lcd.setTextColor(TFT_YELLOW);
  lcd.setTextSize(2);
  lcd.print(Meaning[counter]); 

  delay(5000);
}