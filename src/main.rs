use core::num;
use std::{fmt::Error, result};
use std::num::ParseIntError;
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

fn add(x:i32, y:i32) -> i32 {
    x+y
}
fn change_i32(mut x:i32) {
    x += 4;
    println!("changed:{x}");
}
fn modify_i32(x:&mut i32){
    *x += 4;
}
fn function_copy_by_value() {
   let a = 1;
   let b = 2;
   let c = add(a,b);
   println!("{c}");
   let mut x = 1;
   change_i32(x);
   println!("after change_i32 x:{}", {x});
   modify_i32(&mut x);
   println!("after modify_i32 x:{}", {x});
}


fn move_func(p1:i32, p2:String) {
    println!("p1:{}, p2:{}", p1, p2);
}
fn unmutiable_borrow(p1:i32, p2:&String) {
    println!("p1:{}, p2:{}", p1, (*p2).to_uppercase());
}
#[derive(Debug)]
struct Point1 {
    x:i32,
    y:i32
}
fn mutable_borrow(point:&mut Point1){
    point.x +=1;
    point.y += 2;
}
fn function_param_pass(){
    let n = 12;
    let s = String::from("oo");
    move_func(n, s); //copy i32, move String
    println!("n is {}", n);
    //println!("s is {}", s); //error borrow of moved value.

    let s = String::from("oo");
    unmutiable_borrow(n, &s);
    println!("n is {}", n);
    println!("s is {}", s);

    let mut point = Point1{x:3,y:5};
    println!("{:?}", point);
    mutable_borrow(&mut point);
    println!("{:?}", point);
}

fn func_copy_back() -> i32 {
  let n = 42;
  n
}
fn func_non_copy_back() -> String {
    let s = String::from("hello");
    s  //所有权转移， move
}
fn get_mess(mark:i32) -> &'static str {
 if mark == 0 {
    "smile"
 } else {
    "cry"
 }
}
fn function_return() {
    let i = func_copy_back();
    println!("{i}");
    let s = func_non_copy_back();
    println!("{}", s);
    println!("{}", get_mess(0));
}

fn op_twice(f:fn(i32)->i32, x:i32)->i32 {
    f(f(x))
}
fn mul(x:i32) -> i32 {
    x * x
}
fn add1(x:i32) -> i32 {
 x + 10
}
fn high_order_function_test() {
    let result = op_twice(mul, 3);
    println!("{result}");
    println!("{}", op_twice(add1, 10));

    //数学计算
    let numbers  = vec![1,2,3,4,5,6,7];
    //map
    let res:Vec<_> = numbers.iter().map(|&x| x+x).collect();
    println!("{:?}", res);
    //filter
    //let events:Vec<_> = numbers.into_iter().filter(|&x| x %2 == 0).collect();
    let events = numbers.into_iter().filter(|&x| x %2 == 0).collect::<Vec<_>>();
    println!("{:?}", events);
    //fold/reduce)
    let sum = events.iter().fold(0, |acc, &x| acc +x);
    println!("sum:{}", sum);    
}

//beter to self designed Error
fn devide(a:i32, b:i32) -> Result<f64, String> {
    if b == 0 {
        return Err(String::from("can not devide 0"));
    } else {
        let a = a as f64;
        let b = b as f64;
        return Ok(a/b);
    }   
}
fn find_element(array:&[i32], target:i32) -> Option<usize> {
    for (index, &element) in array.iter().enumerate() {
        if element == target {
            return Some(index);
        }
    }
    None
}
fn result_option_panic_test() {
    //recoverable error:Result/Option
    //unrecoverble error:panic!, abort process.
    //Result
    match devide(1, 2) {
        Ok(number) => println!("result:{}", number),
        Err(e) => println!("devide failed.{:?}", e),
    }
    match devide(1, 0) {
        Ok(number) => println!("result:{}", number),
        Err(e) => println!("devide failed.{:?}", e),
    }
    //Option
    let  arr = [1,2,3,4,5];
    match find_element(&arr, 4) {
        Some(index) =>println!("found target at index:{}", index),
        None => println!("can not find target")
    }
    match find_element(&arr, 7) {
        Some(index) =>println!("found target at index:{}", index),
        None => println!("can not find target")
    }
    //panic!
    let  arr = vec![1,2,3,4,5];
    arr[43];
}

fn find_first_even(numbers:Vec<i32>) -> Option<i32> {
    let first_even = numbers.iter().find(|&x| x % 2 == 0)?; //?如果没找到，会提前返回，不会执持接下来的代码
    println!("Option");
    Some(*first_even)
}
//传递错误
fn parse_numbers(input:&str) -> Result<i32, ParseIntError> {
    let val:i32 = input.parse::<i32>()?;
    Ok(val)
}
fn unwrap_(){
    //unwrap
    let result_ok: Result<i32, &str> = Ok(32);    
    let value = result_ok.unwrap();
    println!("{value}");
    //直接panic
    //let result_ok: Result<i32, &str> = Err("ff");    
    //let value = result_ok.unwrap();
    //println!("{value}");

    //?:Result时如果为Err直接提前返回， Option时如果为None直接提前返回
    //Option
    let numbers = vec![1,2,3,4,5,6];
    match find_first_even(numbers) {
        Some(value) => println!("first even value:{}", value),
        None => println!("No even value found"),
    };
    let numbers = vec![1,3,5];
    match find_first_even(numbers) {
        Some(value) => println!("first even value:{}", value),
        None => println!("No even value found"),
    };
    //Result
    match parse_numbers("d") {
        Ok(value) => println!("parse done, value:{}", value),
        Err(e) => println!("Fail to parse, error:{:?}", e)
    }
    match parse_numbers("3") {
        Ok(value) => println!("parse done, value:{}", value),
        Err(e) => println!("Fail to parse, error:{:?}", e)
    }
}

#[derive(Debug)]
struct MyError {
    detail:String,
}
impl std::fmt::Display for MyError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "Custom Error: {}", self.detail)
    }
}
impl std::error::Error for MyError {
    fn description(&self) -> &str {
        &self.detail
    }
}
fn func() -> Result<(), MyError> {
    Err(MyError{detail:"Custom Error".to_owned()})
}
fn self_def_error_test() -> Result<(), MyError>{
    match func() {
        Ok(_) =>println!("function ok"), 
        Err(e) => println!("Error: {}", e)
    };
    func()?;
    println!("oo");
    Ok(())
}

fn test_borrow_checker() {
    let mut s = String::from("Hello");
    //可以同时有多个不可变引用
    let r1 = &s;
    let r2 = &s;
    println!("{} {}", r1, r2);

    let r3 = &mut s;
    println!("{}", r3);
    //println!("{} {}", r1, r2);  //这时r1, r2就不能再用了，否则会报错can not borrow s as mutable because is it also borrowed as immutable.

    //lifetime
    // let result:&str = "ff"; //定义的同时初始化
    let result:&str;  //定义
    {
        result = "ff"; //初始化
    }
    println!("{}", result);

    let res:&str;
    {
        let r4 = &s;
        res = ff(r4);
    }
    println!("{}", res);
}
//手动声明lifetime
fn ff<'a>(r4: &'a str) -> &'a str {
    r4
}

//每个作为引用的参数都会得到它自己的生命周期参数
//当只有一个输入生命周期时，该生命周期将被分配给所有输出生命周期参数
fn no_need_mark_lifetime(s:&str) -> &str {
    s
}
//s1, s2实际上会被推断为两个不同的lifetime,这里强制将s1, s2声明为相同的生命周期，性能上会有损耗
fn longest<'a>(s1:&'a str, s2:&'a str) -> &'a str{
    if s1.len() > s2.len() {
        s1
    } else {
        s2
    }
}
//使用限定where,更灵活
fn longest_str<'a,'b,'out>(s1:&'a str, s2:&'b str) -> &'out str 
where 
    'a:'out,  //lifetime 'a include lifetime 'b
    'b:'out,
{
    if s1.len() > s2.len() {
        s1
    } else {
        s2
    }
}
//lifetime的主要目的是防止悬垂引用,大多数情况下，lifetime是隐式被推断的
fn test_lifetime_and_function() {
    println!("no need {}", no_need_mark_lifetime("hh"));

    let s1 = "Hello World";
    let s2 = "Hello";
    println!("{}", longest(s1, s2));
    println!("{}", longest_str(s1, s2));

    let result :&str;
    {
        let r2 = "world";
        result = longest_str(s1, s2);
        println!("longest string:{}", result);
    }
}

struct MyString<'a> {
    text:&'a str,
}
impl<'a> MyString<'a> {
    fn get_length(&self) -> usize {
        self.text.len()
    }
    fn modify_data(&mut self)  {
        self.text = "world";
    }
}
//有返回引用的情况
struct StringHolder{
    data:String,
}
impl StringHolder {
    fn get_length(&self)->usize{
        self.data.len()
    }
    //不用手动标注life time，struct带self的函数会自动推断，如get_ref
    fn get_reference<'a>(&'a self) ->&'a String{
        &self.data
    }
    fn get_ref(&self) -> &String {
        &self.data
    }
}
//结构体中的引用需要标注生命周期
//结构体的方法(self等)不需要标注lifetime
//如果有多个输入lifetime, 但其中一个是对self或不可变self的引用时，因为在这种情况下它是一个方法，所以self的lifetime被分配给所有输出lifetime
fn test_lifetime_and_struct() {
    let str1 = String::from("value");
    let mut x = MyString{text:str1.as_str()};
    x.modify_data();
    println!("{}", x.text);

    let mut holder = StringHolder {
        data:String::from("Hello")
    };
    println!("{}", holder.get_reference());
    println!("{}", holder.get_ref());
}
fn main() -> Result<(), Box<dyn std::error::Error>> {
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
    //function_copy_by_value();
    //function_param_pass();   
    //function_return();
    //high_order_function_test();

    //error process
    //result_option_panic_test();
    //unwrap_();
    //self_def_error_test()?; 

    //borrow,lifetime
    //test_borrow_checker();
    //test_lifetime_and_function();
    //test_lifetime_and_struct();
    //尽量不要写出需要自己标注生命周期的代码

    //generic
    Ok(())
}
