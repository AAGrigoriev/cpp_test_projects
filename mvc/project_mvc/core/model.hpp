#pragma once

#include <string>
#include <list>
#include <memory>

#include "objects/IShape.hpp"
#include "observer/observer.hpp"

/*!
    @brief interface class vector editor model
*/
class IModel
{
public:
    IModel()            = default;
    virtual ~IModel()   = default;

    /*!
        @brief Open document from file
        @param[in] file_name 
    */
    virtual void open(std::string &file_name) = 0;

    /*!
        @brief Save document
    */
    virtual void save_document() = 0;

    /*!
        @brief Add primitive to document
        @param[in] shape  
    */
    virtual void addPrimitive(std::unique_ptr<IShape> shape) = 0;

    /*!
        @brief Delete primitive form document
        @param[in] shape  
    */
    virtual void deletePrimitive(std::unique_ptr<IShape> shape) = 0;

    /*!
        @brief Draw all primitive form document
        @param[in]  graphic 
    */
    virtual void draw(std::shared_ptr<IGraphic> graphic) = 0;
};

class Model : public IModel , public IObservable 
{
public:

    Model()             = default;
    virtual ~Model()    = default;

    /*!
        @brief Save document
    */
    virtual void save_document() override;

    /*!
        @brief Open new document
        @param[in] FilePath 
    */
    virtual void open(std::string &FilePath) override;

    /*!
        @brief Add primitive to document
        @param[in] shape  
    */
    virtual void addPrimitive(std::unique_ptr<IShape> shape) override;

    /*!
        @brief Delete primitive from document
        @param[in] shape  
    */

    virtual void deletePrimitive(std::unique_ptr<IShape> shape) override;
    /*!
        @brief Draw all primitive from document
        @param[in] graphic  
    */
    virtual void draw(std::shared_ptr<IGraphic> graphic) override;

private:
    /*!
        @brief  list objects
    */
    std::list<std::unique_ptr<IShape>> list_shapes;

    /*!
        @brief Way to current file
    */
    std::string filePath;
};
