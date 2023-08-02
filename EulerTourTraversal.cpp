template <typename Element, typename ResultType>
class EulerTour
{
protected:
    struct Result
    {
        ResultType leftResult, rightResult, finalResult;
    };
    typedef BinaryTree<Element> BinaryTree;
    typedef typename BinaryTree::Position Position;
protected:
    const BinaryTree* tree;
public:
    void init(const BinaryTree& T) 
    {
        tree = &T;
    }
protected:
    int eulerTour(const Position& p) const;
    virtual void visitExternal(const Position& p, Result& r) const {}
    virtual void visitLeft(const Position& p, Result& r) const {}
    virtual void visitBelow(const Position& p, Result& r) const {}
    virtual void vistRight(const Position& p, Result& r) const {}
    Result initResult() const
    {
        return Result();
    }
    int result(const Result& r) const
    {
        return r.finalResult;
    }
};

template <typename Element, typename ResultType>
int EulerTour<Element, ResultType>::eulerTour(const BinaryTree<Element>::Position& p) const
{
    Result r = initResult();
    if(p.isExternal())
    {
        visitExternal(p, r);
    }
    else
    {
        visitLeft(p, r);
        r.leftResult = eulerTour(p.left());
        visitBelow(p, r);
        r.rightResult = eulerTour(p.right());
        visitRight(p, r);
    }
    return r.finalResult;
}

template <typename Element, typename ResultType>
class EvaluateExpressionTour : public EulerTour<Element, ResultType>
{
protected:
    typedef typename EulerTour<Element, ResultType>::BinaryTree BinaryTree;
    typedef typename EulerTour<Element, ResultType>::Position Position;
    typedef typename EulerTour<Element, ResultType>::Result Result;
public:
    void execute(const BinaryTree& T)
    {
        init(T);
        std::cout << "The value is: " << eulerTour(T.root()) << std::endl;
    }
protected:
    virtual void visitExternal(const Position& p, Result& r) const
    {
        r.finalResult = (*p).value();
    }
    virtual void visitRight(const Position& p, Result& r) const
    {
        r.finalResult = (*p).operation(r.leftResult, r.rightResult);
    }
};

template <typename Element, typename ResultType>
class PrintExpressionTour : public EulerTour<Element, ResultType>
{
protected:
    typedef typename EulerTour<Element, ResultType>::BinaryTree BinaryTree;
    typedef typename EulerTour<Element, ResultType>::Position Position;
    typedef typename EulerTour<Element, ResultType>::Result Result;
public:
    void execute(const BinaryTree& T)
    {
        init(T);
        std::cout << "Expression : ";
        eulerTour(T.root());
        std::cout << std::endl;
    }
protected:
    virtual void visitExternal(const Position& p, Result& r) const
    {
        p -> print();
    }
    virtual void visitLeft(const Position& p, Result& r) const
    {
        std::cout << "(";
    }
    virtual void visitBelow(const Position& p, Result& r) const
    {
        p -> print();
    }
    virtual void visitRight(const Position& p, Result& r) const
    {
        std::cout << ")";
    }
};