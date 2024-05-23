use std::rc::Rc;
use std::collections::VecDeque;
use std::cell::{Cell, RefCell};

trait Animal {
    fn eat(&self);
}
#[derive(Debug)]
struct Cat{
    children:Option<Box<Cat>>
}
impl Animal for Cat {
    fn eat(&self) {
       println!("cat is eating"); 
    }
}
fn test_box_raw_pointer()
{
    //1.解决自己调用自己的问题
    let cat:Box<Cat> = Box::new(Cat{children:None});
    println!("{:?}", cat);

    //2.trait object,比单纯的type object好用很多。
    let t:Box<dyn Animal>;
    t = Box::new(Cat{children:Some(cat)});
    t.eat();

    //3.rust与c++不同，因rust所特有的所有权机器，在Rust中使用原始指针是有风险的
    //Rust中的原始指针：声明需要as来标注类型以有为可变或不可变。解引用则需要用unsafe
    //指向不可变
    let x:usize = 1;
    let raw_point:*const usize = &x as *const usize;
    let raw_point:*const usize = &x;
    //指向可变
    let mut y:usize = 2;
    let raw_mut_point:*mut usize = &mut y as *mut usize;
    let raw_mut_point:*mut usize = &mut y;
    //解引用
    let some_usize = unsafe{*raw_point};
    println!("{some_usize}");
    let some_mut_usize = unsafe {*raw_mut_point};
    println!("{some_mut_usize}");
}

#[derive(Debug)]
struct CatRC{

}
fn test_rc() {
    //解决所有权move的问题
    let cat1 = CatRC{};
    let cat2 = CatRC{};
    let cat3 = CatRC{};

    let cat_v1 = vec!{cat1, cat2};
    //let cat_v2 = vec!{cat2,cat3}; //error:use of moved value cat2

    let cat1 = Rc::new(CatRC{});
    let cat2 = Rc::new(CatRC{});
    let cat3 = Rc::new(CatRC{});
    let cat_v1 = vec!{cat1, Rc::clone(&cat2)}; //cat2 count++
    let cat_v2 = vec!{cat2,cat3}; //cat2 move
    println!("{:?}", cat_v1);
    println!("{:?}", cat_v2);


    //strong_count
    let cat1 = Rc::new(CatRC{});
    let cat2 = Rc::new(CatRC{});
    let cat3 = Rc::new(CatRC{});
    let cat_v1 = vec!{cat1, Rc::clone(&cat2)}; //cat2 count++
    let cat_v2 = vec!{Rc::clone(&cat2),cat3}; //cat2 count++
    println!("cat2 ref count:{}", Rc::strong_count(&cat2));
    println!("{:?}", cat2);
    std::mem::drop(cat_v2);
    println!("cat2 ref count:{}", Rc::strong_count(&cat2));
}

fn test_cell_refcell() {
    //refcell会让来自c++的小伙伴倍感亲切
    //refcell在编译时不报错
    //refcell谨慎使用
    
    //cell,原始类型必须提供copy
    //&str是copy, string不copy
    let c = Cell::new("xyz");
    println!("{:?}",c);
    let c1 = c.get();
    println!("{c1}");
    c.set("abc");
    let c2 = c.get();
    println!("{c1} {c2}");
    let c = Cell::new(String::from("rust"));
    //String未提供copy,以下都不可用
    //println!("{:?}", c);
    //let c3 = c.get();

    
    //refcell
    let r = RefCell::new(String::from("hello"));
    let r1 = r.borrow();
    println!("{r1}");
    //let r1 = r.borrow_mut(); //build时不报错，run的时候会报错
    println!("{r1}");
}

fn main() {
    //why Box?why heap memory
    //在Compile-time无法确定大小
    //数据太大Copy浪费资源
    //想要dyn Trait Object而不是具体的类型
    //test_box_raw_pointer();

    //Rc指针:是存储ref count的胖指针
    //Rc指针的追踪的两个方法：对单个值的多个引用，何时该销毁该变量
    //Rc::clone会创建一个新的Reference,计数加一
    //相对于Arc,Rc指针只能运行于单线程 
    //相对于Weak, Rc是Strong
    //test_rc();

    //Cell与RefCell
    //cell与refcell用于内部可变性，带来了灵活性，同样也带来了一些安全隐患
    //cell与refcell的区别:cell只适用于copy类型，用于提供值，而refcell用于提供引用
    //cell不会panic,而refcell会panic
    test_cell_refcell();
}
