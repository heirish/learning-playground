static MY_STATIC:i32 =42;
static mut MY_MUT_STATIC:i32 =42;

fn const_static_test() {
    const SECOND_HOUR:usize = 3_600;
    const SECOND_DAY:usize = 24 * SECOND_HOUR;
    println!("second_day:{}", SECOND_DAY);

    println!("{MY_STATIC}");
    unsafe{
        MY_MUT_STATIC = 32;
        println!("my mut static:{}", MY_MUT_STATIC);
    }
    //println!("my mut static:{}", MY_MUT_STATIC);
}

fn basic_data_types() {
    let _default_deduce = 32;
    
    //进制的字面量
    let a1 = -125;
    let a2 = 0xFF;
    let a3 = 0o13;
    let a4 = 0b10;
    print!("{a1}, {a2}, {a3}, {a4}");

    //Min Max
    println!("u32 max:{}", u32::MAX);
    println!("u32 min:{}", u32::MIN);
    println!("i32 max:{}", i32::MAX);
    println!("i32 min:{}", i32::MIN);
    println!("usize max:{}", usize::MAX);

    //size
    println!("isize is {} bytes", std::mem::size_of::<isize>());
    println!("usize is {} bytes", std::mem::size_of::<usize>());
    println!("u64 is {} bytes", std::mem::size_of::<u64>());
    println!("i64 is {} bytes", std::mem::size_of::<i64>());
    println!("i32 is {} bytes", std::mem::size_of::<i32>());

    //float
    let f1:f32 = 1.1234;
    let f2:f64 = 9.8888;
    println!("float are {:.2}, {:.2}", f1, f2);

    //bool
    let is_ok = true;
    let can_ok = false;
    println!("{}, {}", is_ok, can_ok);
    println!("or {}, and {}", can_ok||is_ok, can_ok&&is_ok);
   
    //char
    let char_c = 'c';
    let emo_ch = '😃';
    println!("you get a {} feel {}", char_c, emo_ch);
    println!("{}", emo_ch as i32);
    println!("{}", emo_ch as usize);
}

fn tuple_and_array() {
    //tuple
    let tup = (0, "hi", 3.4);
    println!("tuple elements {}, {}, {}", tup.0, tup.1, tup.2);

    let mut tup2 = (0, "hi", 3.4);
    println!("tuple elements {}, {}, {}", tup2.0, tup2.1, tup2.2);
    tup2.1 = "hello";
    //tup2.0 = 'c';
    println!("tuple elements {}, {}, {}", tup2.0, tup2.1, tup2.2);

    let tup3 = ();
    println!("tup3:{:?}", tup3);

    //array
    let mut arr = [11,12,13];
    arr[0]=999;
    println!("arr len {}, first element is {}", arr.len(), arr[0]);
    for elem in arr {
        println!(" {}", elem);
    }
    let ar = [2; 3];
    for i in ar {
        println!(" {}", i);
    }

    //ownership
    let arr_item = [1,2,3];
    let tup_item = (2, "ff");
    println!("arr_item {:?}", arr_item);
    println!("tup_item {:?}", tup_item);
    let arr_ownership = arr_item;
    let tup_ownership = tup_item;
    println!("arr_item {:?}", arr_item);
    println!("tup_item {:?}", tup_item);
    
    let a = 3;
    let b = a;
    println!("{a}");

    //move ownership:struct/string
    let string_item = String::from("aa");
    let string_item_tt = string_item; //string type move ownership 
    //println!("string_item {:?}", string_item); //error:borrow of moved value:value borrowed here after move
    println!("string_item_tt {:?}", string_item_tt); //error:borrow of moved value:value borrowed here after move
}


fn get_length(s:String) -> usize {
    println!("String: {}", s);
    s.len()
    //函数结束之后，调用方的s3也销毁了
}
fn memory_management() {
    //copy move
    //copy
    let c1 = 1;
    let c2 = c1;
    println!("{}", c1);
    //move
    let s1 = String::from("value");
    let s2 = s1;
    //println!("{}", s1); //error, borrow of moved value
    let s3 = s2.clone();
    println!("{}", s2); //s2 still available.
    println!("{}", s3); 
    get_length(s3); //s3 moved in get_length 
    //println!("{}", s3); //error, borrow of moved value

    let back = first_word("hello world");
    println!("{}", back);
    let back = first_word("we are the world");
    println!("{}", back);
}
//can not return reference value
//fn dangle() -> &str { //error missing lifetime specifier
fn dangle() -> String {
   "hello".to_owned()
}
//can input reference and output reference
fn first_word(s:&str) ->&str {
   let bytes = s.as_bytes();
   for(i, &item) in bytes.iter().enumerate() {
    if item == b' ' {
        return &s[0..i];
    }
   } 
   &s[0..]
} 

struct Person {
    name:String, 
    color:String,
    age:i32
}
//可以传&str,也可传String
fn print(data:&str) {
    println!("{}", data)
}
//只能传String
fn print_string_borrow(data:&String) {
    println!("{}", data)
}
fn string_str() {
   //string &str
   let name = String::from("Value C++");
   let course = "Rust".to_owned(); //"Rust".to_string();
   let new_name = name.replace("C++", "cpp");
   println!("{name} {course} {new_name}"); 

   //&str
   let rust = "\x52\x75\x73\x74"; //ascii
   println!("{rust}");

   //struct中成员尽量用string
   let color = "green".to_string();
   let name = "john".to_owned();
   let person = Person {
    name:name,
    color:color,
    age:89
   };

   //func中参数尽量用&str
   let value = "value".to_owned();
   print(&value);
   print("data");
   print_string_borrow(&value);
   //print_string_borrow("dd"); //error: mismatch types
}

//常用enum:Option, Result
enum Color {
    Red,
    Yellow,
    Blue,
    Black
}
fn print_color(my_color:Color) {
    match my_color {
        Color::Red => println!("Red"),
        Color::Yellow=> println!("Yellow"),
        Color::Blue=> println!("Blue"),
        _ => println!("Others")
    }
}
//带内嵌类型的enum
enum BuildingLocation {
    Number(i32),
    Name(String), //不要用&str
    Unknow,
}
impl BuildingLocation {
    fn print_location(&self) {
        match self {
            BuildingLocation::Number(c) => println!("Building Number {}", c) ,
            BuildingLocation::Name(s) => println!("Building Name {}", s),
            _ => println!("Unknown location")
        }
    }
}
fn enum_match() {
    print_color(Color::Red);

    BuildingLocation::Number(23).print_location();
    BuildingLocation::Name("fdfd".to_string()).print_location();
    BuildingLocation::Unknow.print_location();
}

enum Flavor {
    Spicy,
    Sweet,
    Fruity
}
struct Drink {
    flavor:Flavor,
    price:f64,
}
fn print_drink(drink:Drink) {
    match drink.flavor {
        Flavor::Fruity => println!("fruity"),
        Flavor::Spicy=> println!("spicy"),
        Flavor::Sweet=> println!("Sweet"),
        _=> println!("Other"),
    }
    println!("{}", drink.price);
}
impl Drink {
    //关联变量
    const MAX_PRICE:f64=10.0;
    //方法
    fn buy(&self) {
        if self.price > Drink::MAX_PRICE { //Self::MAX_PRICE也可以
            println!("I am poor");
            return;
        }
        println!("buy it");
    }

    //关联函数
    fn new(price:f64) -> Self {
        Drink {
            flavor:Flavor::Fruity,
            price
        }
    }
}
fn struct_() {
    let sweet = Drink{
        flavor:Flavor::Sweet,
        price:6.0};
    println!("{}", sweet.price);
    print_drink(sweet);

    let sweet = Drink{
        flavor:Flavor::Sweet,
        price:16.0};
    sweet.buy();

    let sweet = Drink::new(9.0);
    sweet.buy();
}

struct Counter {
    number:i32,
}
impl Counter {
    fn new(number:i32) ->Self {
        Counter {number}
    }
    //不可变借用
    fn get_number(&self) -> i32{
        self.number
    } //Counter::get_number(self:&Self)

    //可变借用
    fn add(&mut self, increment:i32) {
        self.number += increment;
    } //Counter::add(self:&mut Self, increment:i32)

    //move 1
    fn giveup(self) {
        println!("free {}", self.number);
    }
    //move 2 and return new
    fn combin(c1:Self, c2:Self) -> Self {
        Self {
            number:c1.number + c2.number
        }
    }

}
fn ownership_and_struct() {
    let mut c1 = Counter::new(0);
    println!("c1 number {}", c1.get_number()); 

    c1.add(2);
    println!("c1 number {}", c1.get_number()); 
    c1.giveup();
    //println!("c1 number {}", c1.get_number());  //error:borrow of moved value;

    let c1 = Counter::new(1);
    let c2 = Counter::new(2);
    println!("c1 number {}", c1.get_number()); 
    println!("c2 number {}", c2.get_number()); 
    let c3 = Counter::combin(c1, c2);
    //error:borrow of moved value
    //println!("c1 number {}", c1.get_number()); 
    //println!("c2 number {}", c2.get_number()); 
    println!("c3 number {}", c3.get_number()); 
}

//Box是一个智能指针，它提供对堆分配内存的所有权。它允许你将数据存储在堆上而不是栈上，
//并且在复制或移动时保持对数据的唯一拥有权。
//使用Box可以避免一些内存管理问题，如dangle指针和重复释放
struct Point {
    x:i32,
    y:i32,
}
#[derive(Debug)]
struct Book {
    page:i32,
    rating:f64,
}
#[derive(Debug, Clone, Copy)]
struct BookCopable {
    page:i32,
    rating:f64,
}
fn stack_heap_copy_move() {
    let boxed_point = Box::new(Point{x:10, y:20});
    println!("x:{}, y:{}", boxed_point.x, boxed_point.y);            

    let mut boxed_point = Box::new(32);
    println!("{}", boxed_point);
    println!("{}", *boxed_point);
    *boxed_point += 10;
    println!("{}", *boxed_point);

    //move
    let x = vec![1,2,3,4];
    let y = x;
    println!("{:?}", y);
    //println!("{:?}", x); //error:borrow of moved value

    //clone
    let x = "ss".to_string();
    let y = x.clone();
    println!("{:?}", y);
    println!("{:?}", x);

    let b1 = Book{page:1, rating:0.1};
    let b2 = b1; //move
    //println!("{:?}", b1); //erro:borrow of moved vlaue

    let b1 = BookCopable{page:1, rating:0.1};
    let b2 = b1; //move
    println!("{:?}", b1); //ok
 }

 fn if_match() {
   let age = 50;
   if age < 50 {
    println!("You are young");
   } else {
    println!("You are old");
   }

   //if的表达能力很弱
   let score = 70;
   if score > 90 { 
    println!("good");
   } else if score > 60 {
    println!("ok");
   } else {
    println!("bad");
   }

   let msg =  if age > 50 {"old"} else {"young"};
   println!("{msg}");

    //match, 表达能力更强
    let num = 90;
    match num {
        80 => println!("80"),
        90 => println!("90"),
        _ => println!("else")
    }

    match num {
        25..=50 => println!("[25,50]"),
        51..=100 => println!("[51,100]"),
        _ => println!("others")
    }

    match num {
        25|50|70 => println!("25|50|70"),
        100|200 => println!("100|200"),
        _ => println!("others")
    }

    let num = 60;
    let res = match num {
        x if x < 60 => "bad".to_owned(),
        x if x==60 => "lucky".to_owned(),
        _ => "else".to_owned()
    };
    println!("{res}");
 }

fn loop_iter() {
    //loop
    let mut i = 1;
    loop {
        println!("Ctrl+C");
        std::thread::sleep(std::time::Duration::from_secs(1));
        i += 1;
        if i > 3 {break;}
    }
    let arr = [0,1,2,3,4,5,6,7,8];
    for elem in arr {
        if elem == 7 {
            break;
        }
        if elem == 5 {
            continue;
        }
        print!{" {}", elem};
    }
    println!("");
    
    for i in 0..10 {
        print!(" {}", i);
    }
    println!("");
    //跳出外层loop
    'outer:loop {
        println!("outer");
        loop {
            println!("inner");
            //break;
            break 'outer;
        }
    }

    let numbers = [1,2,3,4,5];
    //循环的写法
    let mut for_numbers = Vec::new();
    for &num in numbers.iter() {
        for_numbers.push(num*num);
    }
    println!("{:?}", for_numbers);
    //迭代的写法
    let numbers = [1,2,3,4,5].to_vec();
    let iter_number:Vec<_> = numbers.iter().map(|&x| x*x).collect();
    println!("{:?}", iter_number);
}
fn main() {
    println!("Hello, world!");
    //const_static_test();
    //basic_data_types();
    //tuple_and_array();

    //ownership, struct, enum
    //memory_management();
    //string_str();
    //enum_match();
    //struct_()
    //ownership_and_struct();
    //stack_heap_copy_move();

    //controlflow, function
    //if_match();
    //loop_iter();
}
